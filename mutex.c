#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 10

int contador = 0;

pthread_mutex_t mutex;

void *incrementa_contador(void *arg) {
    int num_incr = *((int *) arg);
    for (int i = 0; i < num_incr; i++) {
        pthread_mutex_lock(&mutex);
        contador++;
        usleep(1000);
        pthread_mutex_unlock(&mutex);
        printf("Thread %ld incrementou o contador %d vezes\n", pthread_self(), i + 1);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  int num_incr = 100;
  int i, num_threads = NUM_THREADS;
  pthread_mutex_init(&mutex, NULL);
  for (i = 0; i < num_threads; i++) {
    pthread_create(&threads[i], NULL, incrementa_contador, (void *) &num_incr);
  }
  for (i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }
  pthread_mutex_destroy(&mutex);
  printf("Contador: %d\n", contador);
  return 0;
}
