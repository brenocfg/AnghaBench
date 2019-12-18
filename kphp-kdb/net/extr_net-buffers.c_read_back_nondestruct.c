#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pptr; int unprocessed_bytes; int total_bytes; scalar_t__ wptr; scalar_t__ rptr; struct TYPE_3__* prev; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,int) ; 

int read_back_nondestruct (netbuffer_t *H, void *__data, int len) {
  netbuffer_t *X = H->prev;
  int s, w = 0;
  char *data = __data ? (char *) __data + len : 0;
  if (H->pptr) {
    if (len > H->unprocessed_bytes) {
      len = H->unprocessed_bytes;
    }
  } else {
    if (len > H->total_bytes) {
      len = H->total_bytes;
    }
  }

  if (X->wptr == X->rptr && X != H) {
    X = X->prev;
  }

  while (len > 0) {
    s = X->wptr - (X->pptr ? X->pptr : X->rptr);
    if (s > len) { s = len; }
    if (s > 0) {
      if (data) {
        memcpy (data -= s, X->wptr - s, s);
      }
      w += s;
      len -= s;
    }
    if (len > 0) {
      X = X->prev;
    }
  }

  return w;
}