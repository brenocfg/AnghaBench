#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ state; scalar_t__ rptr; scalar_t__ wptr; scalar_t__ start; scalar_t__ pptr; int extra; struct TYPE_4__* next; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_HEAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_buffer (TYPE_1__*) ; 

void free_unused_buffers (netbuffer_t *H) {
  netbuffer_t *X = H->next, *Y;
  assert (H->state == NB_MAGIC_HEAD || H->state == NB_MAGIC_BUSYHEAD);
  if (H->rptr == H->wptr) {
    H->rptr = H->wptr = H->start;
    if (H->pptr) {
      H->pptr = H->wptr;
    }
  }
  while (X != H && X->rptr == X->wptr) {
    //fprintf (stderr, "freeing unused write buffer %p (prev=%p) for connection %d, total=%d\n",
    //	X, X->prev, H->extra);
    H->next = Y = X->next;
    Y->prev = H;
    assert (H->extra > 0);
    free_buffer(X);
    H->extra--;
    X = Y;
  }
  if (X == H) {
    assert (!H->extra);
    return;
  }
  X = H->prev;
  assert (X != H);
  while (X->rptr == X->wptr) {
    //fprintf (stderr, "freeing unused write buffer %p (prev=%p) for connection %d, total=%d\n",
    //	X, X->prev, H->extra);
    H->prev = Y = X->prev;
    assert (Y != H && H->extra > 1);
    Y->next = H;
    free_buffer(X);
    H->extra--;
    X = Y;
    assert (X != H);
  }
}