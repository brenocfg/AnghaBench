#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ wptr; scalar_t__ rptr; int pptr; int total_bytes; scalar_t__ start; scalar_t__ extra; struct TYPE_6__* next; struct TYPE_6__* prev; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_buffer (TYPE_1__*) ; 
 scalar_t__ write_out (TYPE_1__*,int,int) ; 

int copy_through (netbuffer_t *HD, netbuffer_t *H, int len) {
  netbuffer_t *X = H, *Y;
  int s, w = 0;
  if (X->wptr == X->rptr) {
    X = X->next;
  }
  while (len > 0) {
    s = (X->pptr ? X->pptr : X->wptr) - X->rptr;
    if (s > len) { s = len; }
    if (s > 0) {
      w += write_out (HD, X->rptr, s);
      X->rptr += s;
      len -= s;
      H->total_bytes -= s;
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
    } else if (X->rptr == X->pptr) {
      break;
    }
  }
  return w;
}