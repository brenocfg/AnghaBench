#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ magic; scalar_t__ rptr; scalar_t__ eptr; scalar_t__ wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_BUFFER_MAGIC ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* outbuf ; 
 int /*<<< orphan*/  store ; 

__attribute__((used)) static int do_rpc_store_set_pos (int p) { /* {{{ */
  ADD_CNT (store);
  START_TIMER (store);
  assert (outbuf && outbuf->magic == RPC_BUFFER_MAGIC);
  if (p < 0 || outbuf->rptr + p > outbuf->eptr) {
    return 0;
  }
  outbuf->wptr = outbuf->rptr + p;
  END_TIMER (store);
  return 1;
}