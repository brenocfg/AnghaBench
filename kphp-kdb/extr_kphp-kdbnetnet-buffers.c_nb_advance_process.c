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
struct TYPE_4__ {scalar_t__ pptr; scalar_t__ wptr; int total_bytes; int unprocessed_bytes; struct TYPE_4__* next; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ netbuffer_t ;
struct TYPE_5__ {scalar_t__ ptr0; int len0; int len1; scalar_t__ ptr1; TYPE_1__* cur; TYPE_1__* head; } ;
typedef  TYPE_2__ nb_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int nb_advance_process (nb_processor_t *P, int offset) {
  netbuffer_t *H = P->head, *X = P->cur;
  int s, w = 0;

  assert (H && offset >= 0);

  while (offset > 0 || X->pptr == X->wptr) {
    s = X->wptr - X->pptr;
    if (s > offset) { s = offset; }
    if (s > 0) {
      w += s;
      X->pptr += s;
      offset -= s;
    }
    if (X->pptr == X->wptr) {
      X = X->next;
      if (X == H) { 
        assert (!offset);
        X = 0;
        break; 
      }
    }
  }

  H->total_bytes += w;
  H->unprocessed_bytes -= w;

  if (X == P->cur) {
    P->ptr0 += w;
    P->len0 -= w;
    assert (P->len0 > 0 && P->ptr0 == X->pptr);
    return P->len0 + P->len1;
  }

  if (!X) {
    assert (!H->unprocessed_bytes);
    P->cur = H->prev;
    P->ptr0 = 0;
    P->ptr1 = 0;
    P->len0 = 0;
    P->len1 = 0;
    return 0;
  }
  
  P->cur = X;

  P->ptr0 = X->pptr;
  P->len0 = X->wptr - X->pptr;

  assert (P->len0 > 0);

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