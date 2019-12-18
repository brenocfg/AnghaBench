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
struct TYPE_3__ {scalar_t__ state; scalar_t__ wptr; scalar_t__ end; int total_bytes; int unprocessed_bytes; int /*<<< orphan*/  pptr; struct TYPE_3__* prev; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_HEAD ; 
 int NET_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 

void advance_write_ptr (netbuffer_t *H, int offset) {
  netbuffer_t *X = H->prev;
  assert (H->state == NB_MAGIC_HEAD || H->state == NB_MAGIC_BUSYHEAD);
  assert (offset > 0 && offset <= NET_BUFFER_SIZE);
  X->wptr += offset;
  assert (X->wptr <= X->end);
  if (!X->pptr) {
    H->total_bytes += offset;
  } else {
    H->unprocessed_bytes += offset;
  }
}