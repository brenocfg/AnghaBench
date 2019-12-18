#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pptr; scalar_t__ rptr; scalar_t__ wptr; scalar_t__ unprocessed_bytes; struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ netbuffer_t ;
struct TYPE_6__ {scalar_t__ ptr0; scalar_t__ ptr1; scalar_t__ len0; scalar_t__ len1; TYPE_1__* cur; TYPE_1__* head; } ;
typedef  TYPE_2__ nb_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int nb_start_process (nb_processor_t *P, netbuffer_t *H) {
  P->head = H;
  netbuffer_t *X;
  for (X = H->prev; X != H && X->pptr == X->rptr; X = X->prev) {
    assert (X->pptr);
  };
  while (X->next != H && X->pptr == X->wptr) {
    X = X->next;
  }

  P->cur = X;

  if (X->pptr == X->wptr) {
    assert (!H->unprocessed_bytes);
    P->ptr0 = 0;
    P->ptr1 = 0;
    P->len0 = 0;
    P->len1 = 0;
    return 0;
  }

  P->ptr0 = X->pptr;
  P->len0 = X->wptr - X->pptr;

  X = X->next;
  if (X == H || X->pptr == X->wptr) {
    P->ptr1 = 0;
    P->len1 = 0;
  } else {
    P->ptr1 = X->pptr;
    P->len1 = X->wptr - X->pptr;
  }

  assert (P->len0 + P->len1 <= H->unprocessed_bytes);

  return P->len0 + P->len1;
}