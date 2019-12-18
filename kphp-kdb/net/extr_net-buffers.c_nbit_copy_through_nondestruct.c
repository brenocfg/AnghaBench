#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* rptr; char* wptr; char* pptr; struct TYPE_6__* next; } ;
typedef  TYPE_1__ netbuffer_t ;
struct TYPE_7__ {char* cptr; TYPE_1__* cur; TYPE_1__* head; } ;
typedef  TYPE_2__ nb_iterator_t ;

/* Variables and functions */
 unsigned int NET_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  write_out (TYPE_1__*,char*,int) ; 

int nbit_copy_through_nondestruct (netbuffer_t *XD, nb_iterator_t *I, int len) {
  netbuffer_t *H = I->head, *X = I->cur;
  int s, w = 0;
  char *p = I->cptr;

  assert (X->rptr <= p && p <= X->wptr);
  assert (!X->pptr || p <= X->pptr);

  while (len > 0) {
    s = (X->pptr ? X->pptr : X->wptr) - p;
    assert ((unsigned) s <= NET_BUFFER_SIZE);
    if (s > len) { s = len; }
    if (s > 0) {
      write_out (XD, p, s);
      w += s;
      p += s;
      len -= s;
    }
    if (!len || p != X->wptr || X->next == H) { 
      break; 
    }
    X = X->next;
    p = X->rptr;
  }
  return w;
}