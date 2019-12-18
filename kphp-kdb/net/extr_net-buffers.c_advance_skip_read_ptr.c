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
struct TYPE_4__ {scalar_t__ wptr; scalar_t__ rptr; scalar_t__ pptr; scalar_t__ start; scalar_t__ extra; int total_bytes; struct TYPE_4__* next; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_buffer (TYPE_1__*) ; 

int advance_skip_read_ptr (netbuffer_t *H, int len) {
  netbuffer_t *X = H, *Y;
  int s, t = 0, w = 0;
  if (X->wptr == X->rptr) {
    X = X->next;
  }
  while (len > 0) {
    s = X->wptr - X->rptr;
    if (X->pptr && X->pptr < X->wptr) {
      s = X->pptr - X->rptr;
      t = 1;
    }
    if (s > len) { s = len; }
    if (s > 0) {
      w += s;
      X->rptr += s;
      len -= s;
    }
    if (X->rptr == X->wptr) {
      if (X == H) { 
	X->rptr = X->wptr = X->start;
	if (X->pptr) {
	  X->pptr = X->wptr;
	}
	X = X->next;
      } else {
	Y = X->next;
	assert (H->extra > 0);
	Y->prev = H;
	H->next = Y;
	free_buffer (X);
	H->extra--;
	X = Y;
      }
      if (X == H) { break; }
    }
    if (!len || t) { break; }
  }
  H->total_bytes -= w;
  return w;
}