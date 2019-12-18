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
struct connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote_pid; } ;

/* Variables and functions */
 TYPE_1__* RPCS_DATA (struct connection*) ; 
 int RPC_INVOKE_REQ ; 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/ * TL_IN_PID ; 
 int /*<<< orphan*/  WaitAioArrClear () ; 
 int /*<<< orphan*/  rpc_target_insert_conn (struct connection*) ; 
 int tl_query_act (struct connection*,int,int) ; 

int default_tl_rpcs_execute (struct connection *c, int op, int len) {
  rpc_target_insert_conn (c);
  if (op != RPC_INVOKE_REQ) {
    return SKIP_ALL_BYTES;
  }
  TL_IN_PID = &RPCS_DATA(c)->remote_pid;
  WaitAioArrClear ();
  return tl_query_act (c, op, len);
}