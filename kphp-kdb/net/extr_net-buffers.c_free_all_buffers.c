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
struct TYPE_4__ {scalar_t__ state; scalar_t__ extra; scalar_t__ pptr; int /*<<< orphan*/  start; int /*<<< orphan*/  wptr; int /*<<< orphan*/  rptr; struct TYPE_4__* next; struct TYPE_4__* prev; scalar_t__ unprocessed_bytes; scalar_t__ total_bytes; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_HEAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_buffer (TYPE_1__*) ; 

void free_all_buffers (netbuffer_t *H) {
  netbuffer_t *X, *Y;
  if (!H) { return; }
  assert (H->state == NB_MAGIC_HEAD || H->state == NB_MAGIC_BUSYHEAD);
  X = H->next;
  while (X != H) {
    assert (H->extra > 0);
    Y = X->next;
    free_buffer (X);
    H->extra--;
    X = Y;
  }
  assert (!H->extra);
  H->total_bytes = 0;
  H->unprocessed_bytes = 0;
  H->prev = H->next = H;
  H->rptr = H->wptr = H->start;
  H->pptr = 0;

  if (H->state == NB_MAGIC_BUSYHEAD) {
    free_buffer (H);
  }
}