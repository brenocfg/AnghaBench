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
struct TYPE_4__ {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_BUFFER_MAGIC ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int TL_RPC_DEST_ACTOR ; 
 int TL_RPC_DEST_ACTOR_FLAGS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_write_int (TYPE_1__*,int) ; 
 int /*<<< orphan*/  buffer_write_long (TYPE_1__*,long long) ; 
 TYPE_1__* outbuf ; 
 int /*<<< orphan*/  store ; 

__attribute__((used)) static void do_rpc_store_header (long long cluster_id, int flags) { /* {{{ */
  ADD_CNT (store);
  START_TIMER (store);
  assert (outbuf && outbuf->magic == RPC_BUFFER_MAGIC);
  if (flags) {
    buffer_write_int (outbuf, TL_RPC_DEST_ACTOR_FLAGS);
    buffer_write_long (outbuf, cluster_id);
    buffer_write_int (outbuf, flags);
  } else {
    buffer_write_int (outbuf, TL_RPC_DEST_ACTOR);
    buffer_write_long (outbuf, cluster_id);
  }
  END_TIMER (store);
}