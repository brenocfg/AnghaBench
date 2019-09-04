#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* rptr; char* wptr; char* pptr; struct TYPE_4__* next; } ;
typedef  TYPE_1__ netbuffer_t ;
struct TYPE_5__ {char* cptr; TYPE_1__* cur; TYPE_1__* head; } ;
typedef  TYPE_2__ nb_iterator_t ;

/* Variables and functions */
 unsigned int NET_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

int nbit_read_in (nb_iterator_t *I, void *__data, int len) {
  netbuffer_t *H = I->head, *X = I->cur;
  int s, w = 0;
  char *data = __data, *p = I->cptr;

  assert (X->rptr <= p && p <= X->wptr);
  assert (!X->pptr || p <= X->pptr);

  while (len > 0) {
    s = (X->pptr ? X->pptr : X->wptr) - p;
    assert ((unsigned) s <= NET_BUFFER_SIZE);
    if (s > len) { s = len; }
    if (s > 0) {
      memcpy (data, p, s);
      w += s;
      p += s;
      data += s;
      len -= s;
    }
    if (!len || p != X->wptr || X->next == H) { 
      break; 
    }
    X = X->next;
    p = X->rptr;
  }
  if (p == X->wptr && X->next != H) {
    X = X->next;
    p = X->rptr;
  }
  I->cptr = p;
  I->cur = X;
  return w;
}