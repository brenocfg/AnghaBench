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
struct TYPE_4__ {scalar_t__ state; scalar_t__ rptr; scalar_t__ wptr; scalar_t__ pptr; scalar_t__ extra; scalar_t__ start; int total_bytes; struct TYPE_4__* prev; struct TYPE_4__* next; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_HEAD ; 
 int NET_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_buffer (TYPE_1__*) ; 

void advance_read_ptr (netbuffer_t *H, int offset) {
  netbuffer_t *X = H, *Y;
  assert (H->state == NB_MAGIC_HEAD || H->state == NB_MAGIC_BUSYHEAD);
  assert (offset >= 0 && offset <= NET_BUFFER_SIZE);
  if (H->rptr == H->wptr) {
    X = H->next;
    X->rptr += offset;
    assert (X->rptr <= X->wptr);
    assert (!X->pptr || X->rptr <= X->pptr);
    if (X->rptr == X->wptr) {
      Y = X->next;
      assert (H->extra > 0);	// may fail if buffer chain empty and offset=0
      H->next = Y;
      Y->prev = H;
      free_buffer (X);
      H->extra--;
    }
  } else {
    H->rptr += offset;
    assert (H->rptr <= H->wptr);
    assert (!H->pptr || H->rptr <= H->pptr);
    if (H->rptr == H->wptr) {
      H->rptr = H->wptr = H->start;
      if (H->pptr) {
        H->pptr = H->wptr;
      }
    }
  }
  H->total_bytes -= offset;
}