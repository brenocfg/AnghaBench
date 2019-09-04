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
struct TYPE_4__ {scalar_t__ rptr; scalar_t__ wptr; int pptr; scalar_t__ state; int extra; struct TYPE_4__* next; } ;
typedef  TYPE_1__ netbuffer_t ;
struct TYPE_5__ {scalar_t__ cptr; TYPE_1__* cur; TYPE_1__* head; } ;
typedef  TYPE_2__ nb_iterator_t ;

/* Variables and functions */
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_HEAD ; 
 int NET_BUFFERS ; 
 unsigned int NET_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 

int nbit_ready_bytes (nb_iterator_t *I) {
  netbuffer_t *H = I->head, *X = I->cur;
  int limit, v;
  if (!H) {
    return 0;
  }
  assert (X->rptr <= X->wptr);
  assert (X->rptr <= I->cptr && I->cptr <= X->wptr);
  if (I->cptr < X->wptr) {
    return (X->pptr ? X->pptr : X->wptr) - I->cptr;
  }
  assert (H->state == NB_MAGIC_HEAD || H->state == NB_MAGIC_BUSYHEAD);
  limit = H->extra + 1;
  assert (limit <= NET_BUFFERS + 12);

  X = X->next;
  while (X != H) {
    assert (--limit >= 0);
    v = X->wptr - X->rptr;
    assert ((unsigned) v <= NET_BUFFER_SIZE);
    if (v) {
      I->cur = X;
      I->cptr = X->rptr;
      if (X->pptr) {
        v = X->pptr - X->rptr;
      }
      return v;
    }
    X = X->next;
  }
  return 0;
}