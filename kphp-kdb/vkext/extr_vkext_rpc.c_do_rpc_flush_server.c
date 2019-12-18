#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rpc_server {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_flush ; 
 scalar_t__ rpc_flush_out_force (struct rpc_server*,double) ; 
 int /*<<< orphan*/  rpc_server_failure (struct rpc_server*) ; 
 scalar_t__ rpc_status_connected ; 

int do_rpc_flush_server (struct rpc_server *server, double timeout) { /* {{{ */
  ADD_CNT (rpc_flush);
  START_TIMER (rpc_flush);
  if (!server || server->status != rpc_status_connected) {
    END_TIMER (rpc_flush);
    return 0;
  }
  if (rpc_flush_out_force (server, timeout) < 0) {
    rpc_server_failure (server);
    END_TIMER (rpc_flush);
    return -1;
  } else {
    END_TIMER (rpc_flush);
    return 1;
  }
}