/*
 * Implementation of the word_count interface using Pintos lists.
 *
 * You may modify this file, and are expected to modify it.
 */

/*
 * Copyright © 2021 University of California, Berkeley
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PINTOS_LIST
#error "PINTOS_LIST must be #define'd when compiling word_count_l.c"
#endif

#include "word_count.h"

void init_words(word_count_list_t* wclist) {
  list_init(wclist);
}

size_t len_words(word_count_list_t* wclist) {
/*  word_count_list* curr ;r
  size_t res = 0;
  for(curr = list_begin(wclist); e!=list_end(wclist); curr = list_next(e)){
    res++;
  }
  return res;
*/
  return list_size(wclist);
}

word_count_t* find_word(word_count_list_t* wclist, char* word) {
 struct list_elem * curr;
  for(curr = list_begin(wclist); curr!=list_end(wclist); curr = list_next(curr)){
    word_count_t * w = list_entry(curr, word_count_t,elem);
    if(strcmp(w->word,word)==0){
      return w;
    }
  }
  return NULL;
}

word_count_t* add_word(word_count_list_t* wclist, char* word) {
  word_count_t * fw = find_word(wclist, word); 
  if( fw != NULL){
    fw->count++;
  } else if((fw = (word_count_t*) malloc(sizeof(word_count_t)))!= NULL){
    fw->word = word;
    fw->count = 1;
    struct list_elem* insert = &fw->elem;
    list_push_back(wclist, insert);
  }else {
    perror("malloc");
  }
  return fw;
}

void fprint_words(word_count_list_t* wclist, FILE* outfile) { /* TODO */
  struct list_elem* curr = list_begin(wclist);
  if(outfile != NULL){
    while(curr != list_end(wclist)){
      word_count_t* w = list_entry(curr,word_count_t,elem);
      if(w != NULL){
        fprintf(outfile,"%8d\t%s\n",w->count,w->word);
      }
      curr = list_next(curr); 
    }
  }
}

static bool less_list(const struct list_elem* ewc1, const struct list_elem* ewc2, void* aux) {
  word_count_t* wc1 = list_entry(ewc1, word_count_t, elem);
  word_count_t* wc2 = list_entry(ewc2, word_count_t, elem);
  if(strcmp(wc1->word,wc2->word) >= 0){
    return false;
  } else{
    return true;
  }
}

void wordcount_sort(word_count_list_t* wclist,
                    bool less(const word_count_t*, const word_count_t*)) {
  list_sort(wclist, less_list, less);
}

