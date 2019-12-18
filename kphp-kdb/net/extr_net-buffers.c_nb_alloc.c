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
struct TYPE_4__ {scalar_t__ state; int wptr; int end; int total_bytes; int /*<<< orphan*/  extra; struct TYPE_4__* prev; struct TYPE_4__* next; int /*<<< orphan*/  pptr; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_HEAD ; 
 int NETBUFF_DATA_SIZE ; 
 TYPE_1__* alloc_buffer () ; 
 int /*<<< orphan*/  assert (int) ; 

void *nb_alloc (netbuffer_t *H, int len) {
  netbuffer_t *X, *Y;
  int s, t;
  void *res;
  if (!H || len < 0 || len > NETBUFF_DATA_SIZE) { return 0; }
  assert (H->state == NB_MAGIC_HEAD || H->state == NB_MAGIC_BUSYHEAD);
  assert (!H->pptr);

  X = H->prev;
  t = -((long) X->wptr) & 3;
  s = X->end - X->wptr; 

  if (len + t <= s) {
    res = X->wptr += t;
    X->wptr += len;
    H->total_bytes += len;
    return res;
  }

  Y = alloc_buffer();
  if (!Y) { return 0; }

  X->next = Y;
  Y->prev = X;
  Y->next = H;
  H->prev = Y;
  H->extra++;

  s = Y->end - Y->wptr; 

  if (len <= s) {
    res = Y->wptr;
    Y->wptr += len;
    H->total_bytes += len;
    return res;
  }

  return 0;
}