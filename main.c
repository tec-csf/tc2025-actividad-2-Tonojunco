/***********************
 Apuntadores a funciones
 Trabaje con Luis Daniel Roa y Luis Ortiz Revilla

 Antonio Junco de Haas A01339695
 **************************/
#include <stdio.h>
#include <stdlib.h>

#define I 10
#define N 5

typedef struct
{
  char * titulo;
  int paginas;
} Libro;

typedef void (*d_print)(void *);
typedef void (*t_recorre)(void *, size_t, size_t,d_print);
//void recorre(t_recorre, void *, size_t, size_t,d_print);



void *begin(void *vector){
  return vector;
}

void *end(void *vector, size_t count, size_t size){
  return vector + ((count * size) - size);
}

void *next(void *vector, void *current, size_t count, size_t size){
  void * next = current + size;
  void * final = end(vector, count, size);
  if(next > final) {
    return NULL;
  }
  return next;
}

void *prev(void *vector, void *current, size_t count, size_t size){
  void * prev = current - size;
  void * start = begin(vector);
  if(prev < start) {
    return NULL;
  }
  return prev;
}

void forward(void*vector,size_t count, size_t size, d_print a){
  void * aux_forward=begin(vector);

  while(aux_forward!=NULL){
    (*a)(aux_forward);
    aux_forward=next(vector, aux_forward, count, size);
  }

}

void backwards(void*vector,size_t count, size_t size, d_print a){
  void * aux_backwards=end(vector,count,size);

  while(aux_backwards!=NULL){
    (*a)(aux_backwards);
    aux_backwards=prev(vector, aux_backwards, count, size);
  }

}
void bidirectional(void*vector,size_t count, size_t size, d_print a){
  printf("\nForward\n");
  forward(vector,count,size,a);
  printf("\nBackwards\n");
  backwards(vector,count,size,a);
  printf("\n");

}


void recorre(t_recorre direccion, void *vector, size_t count, size_t size, d_print a){
  (*direccion)(vector,count,size, a);
}



void imprimeInt(int * printthis)
{
    printf(" %d ", *printthis);
}


void imprimeTitulo(Libro * printthis){
  printf(" %s \t %d",printthis->titulo,printthis->paginas);

}


int main (int arc, const char * argv[])
{
  int * vector = (int *) malloc(N * sizeof(int));

  int * aux = vector;
  int * last = vector + N;

  for (; aux < last; ++aux) {

      *aux = rand() % 100;
      printf(" %d\t ",*aux);
  }
  printf("\n");
  recorre(&forward,vector,N,sizeof(int),&imprimeInt);
  printf("\n");
  recorre(&bidirectional,vector,N,sizeof(int),&imprimeInt);
  //recorre(&backwards,vector,N,sizeof(int),&imprimeInt);



  Libro * tomo = (Libro *)malloc(sizeof(Libro) * N);
  Libro * auxLibro=tomo;
    Libro * fin = tomo + N;

	    for (Libro * auxLibro = tomo; auxLibro < fin; ++auxLibro)
	    {
	        auxLibro->titulo = (char *)malloc(sizeof(char) * 20);
	        printf("\nNombre del libro: ");
	        scanf("%s", auxLibro->titulo);

	        printf("Número de páginas: ");
	        scanf("%d", &auxLibro->paginas);
	    }
      printf("\n");
      recorre(&bidirectional,tomo,N,sizeof(Libro),&imprimeTitulo);
      //recorre(&forward,tomo,N,sizeof(Libro),&imprimeTitulo);
      //recorre(&backwards,tomo,N,sizeof(Libro),&imprimeTitulo);


  free(vector);
  printf("\n");
  for (auxLibro=tomo;auxLibro<fin;++auxLibro){

    free(auxLibro->titulo);
  }

  free(tomo);



}
