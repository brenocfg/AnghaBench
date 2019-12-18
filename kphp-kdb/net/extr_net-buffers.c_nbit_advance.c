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
struct TYPE_4__ {char* rptr; char* wptr; char* pptr; struct TYPE_4__* prev; struct TYPE_4__* next; } ;
typedef  TYPE_1__ netbuffer_t ;
struct TYPE_5__ {char* cptr; TYPE_1__* cur; TYPE_1__* head; } ;
typedef  TYPE_2__ nb_iterator_t ;

/* Variables and functions */
 unsigned int NET_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 

int nbit_advance (nb_iterator_t *I, int offset) {
  netbuffer_t *X = I->cur, *H = I->head;
  int u, v = 0, t = 0;
  char *p = I->cptr;

  if (!offset || !I->cur) {
    return 0;
  }

  assert (X->rptr <= p && p <= X->wptr);
  assert (!X->pptr || p <= X->pptr);

  if (offset > 0) {
    u = X->wptr - p;
    if (X->pptr && X->pptr != X->wptr) {
      u = X->pptr - p;
      t = 1;
    }
    v = 0;

    do {
      if (u > offset) {
        I->cptr = p + offset;
        I->cur = X;
        return v + offset;
      }
      v += u;
      offset -= u;
      if (t) {
        I->cptr = X->pptr;
        I->cur = X;
        return v;
      }
      if (X->next == H) {
        assert (!X->pptr || X->pptr == X->wptr);
        I->cptr = X->wptr;
        I->cur = X;
        return v;
      }
      X = X->next;
      p = X->rptr;
      u = X->wptr - p;
      if (X->pptr && X->pptr != X->wptr) {
        u = X->pptr - p;
        t = 1;
      }
      assert ((unsigned) u <= NET_BUFFER_SIZE);
    } while (offset > 0);

    I->cptr = p;
    I->cur = X;
    return v;

  } else {
    u = p - X->rptr;
    v = 0;

    do {
      if (u + offset >= 0) {
        I->cptr = p + offset;
        I->cur = X;
        return v + offset;
      }
      v -= u;
      offset += u;
      if (X == H) {
        I->cptr = X->rptr;
        I->cur = X;
        return v;
      }
      X = X->prev;
      p = X->wptr;
      assert (!X->pptr || p == X->pptr);
      u = p - X->rptr;
      assert ((unsigned) u <= NET_BUFFER_SIZE);
    } while (offset < 0);

    I->cptr = p;
    I->cur = X;
    return v;
  }
}