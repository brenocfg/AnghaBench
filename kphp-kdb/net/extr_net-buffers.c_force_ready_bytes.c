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
struct TYPE_5__ {scalar_t__ state; int wptr; int rptr; scalar_t__ pptr; int start; int end; scalar_t__ extra; int total_bytes; struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_HEAD ; 
 int NET_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int,int,int) ; 
 int /*<<< orphan*/  memmove (int,int,int) ; 
 int read_in (TYPE_1__*,int,int) ; 

int force_ready_bytes (netbuffer_t *H, int sz) {
  int u, v, w;
  netbuffer_t *X, *Y;
  assert (H->state == NB_MAGIC_HEAD || H->state == NB_MAGIC_BUSYHEAD);
  assert (sz >= 0);
  u = H->wptr - H->rptr;
  if (H->pptr && H->pptr != H->wptr) {
    assert (H->rptr <= H->pptr && H->pptr < H->wptr);
    return H->pptr - H->rptr;
  }
  if (sz <= u || H->next == H) { return u; }
  if (sz > NET_BUFFER_SIZE) { sz = NET_BUFFER_SIZE; }
  X = H->next;
  v = (X->pptr ? X->pptr : X->wptr) - X->rptr;
  assert ((unsigned) v <= NET_BUFFER_SIZE);
  if (u + v >= sz || X->next == H) {
    if (!v) { return u; }
    if (u <= X->rptr - X->start) {
      X->rptr -= u;
      memcpy (X->rptr, H->rptr, u);
      H->rptr = H->wptr = H->start;
      if (H->pptr) {
        H->pptr = H->start;
      }
      return u + v;
    }
    if (v > sz - u) { v = sz - u; }
    w = H->end - H->wptr;
    if (v > w) {
      memmove (H->start, H->rptr, u);
      H->rptr = H->start;
      H->wptr = H->start + u;
      w = H->end - H->wptr;
    }
    if (v > w) { v = w; }
    memcpy (H->wptr, X->rptr, v);
    X->rptr += v;
    H->wptr += v;
    if (H->pptr) {
      H->pptr = H->wptr;
    }
    if (X->rptr == X->wptr) {
      Y = X->next;
      assert (H->extra > 0);
      H->next = Y;
      Y->prev = H;
      free_buffer (X);
      H->extra--;
    }
    return u + v;
  }
  // this case is quite rare
  if (u > 0) {
    memmove (H->start, H->rptr, u);
  }
  H->rptr = H->wptr = H->start;
  if (H->pptr) {
    H->pptr = H->wptr;
  }
  if (sz > H->end - H->start) {
    sz = H->end - H->start;
  }
  w = read_in (H, H->wptr + u, sz - u);
  v = u + w;
  H->total_bytes += w;
  H->wptr += v;
  if (H->pptr) {
    H->pptr = H->wptr;
  }
  return v;
}