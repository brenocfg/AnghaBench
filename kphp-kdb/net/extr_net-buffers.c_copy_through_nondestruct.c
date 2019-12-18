#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* wptr; char* rptr; char* pptr; struct TYPE_5__* next; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 scalar_t__ write_out (TYPE_1__*,char*,int) ; 

int copy_through_nondestruct (netbuffer_t *HD, netbuffer_t *H, int len) {
  netbuffer_t *X = H;
  int s, w = 0;
  char *rptr;
  if (X->wptr == X->rptr) {
    X = X->next;
  }
  rptr = X->rptr;
  while (len > 0) {
    s = (X->pptr ? X->pptr : X->wptr) - rptr;
    if (s > len) { s = len; }
    if (s > 0) {
      w += write_out (HD, rptr, s);
      rptr += s;
      len -= s;
    }
    if (rptr == X->wptr) {
      X = X->next;
      rptr = X->rptr;
      if (X == H) { break; }
    } else if (rptr == X->pptr) {
      break;
    }
  }
  return w;
}