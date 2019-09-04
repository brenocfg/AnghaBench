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
struct TYPE_3__ {scalar_t__ state; int pptr; scalar_t__ unprocessed_bytes; int /*<<< orphan*/  total_bytes; struct TYPE_3__* next; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_HEAD ; 
 int /*<<< orphan*/  assert (int) ; 

int release_all_unprocessed (netbuffer_t *H) {
  netbuffer_t *X;
  assert (H->state == NB_MAGIC_HEAD || H->state == NB_MAGIC_BUSYHEAD);
  assert (H->pptr);
  H->pptr = 0;
  for (X = H->next; X != H; X = X->next) {
    assert (X->pptr);
    X->pptr = 0;
  }
  H->total_bytes += H->unprocessed_bytes;
  H->unprocessed_bytes = 0;
  return 0;
}