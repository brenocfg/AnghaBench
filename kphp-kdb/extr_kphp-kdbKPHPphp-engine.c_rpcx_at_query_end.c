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
struct rpcs_data {int /*<<< orphan*/ * extra; } ;
struct connection {scalar_t__ status; int /*<<< orphan*/  flags; scalar_t__ pending_queries; scalar_t__ generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_REPARSE ; 
 struct rpcs_data* RPCS_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_connection_timeout (struct connection*) ; 
 scalar_t__ conn_generation ; 
 scalar_t__ conn_wait_net ; 
 int /*<<< orphan*/  has_pending_scripts () ; 
 int lease_ready_flag ; 
 int /*<<< orphan*/  run_rpc_lease () ; 

void rpcx_at_query_end (struct connection *c) {
  struct rpcs_data *D = RPCS_DATA(c);

  clear_connection_timeout (c);
  c->generation = ++conn_generation;
  c->pending_queries = 0;
  D->extra = NULL;

  if (!has_pending_scripts()) {
    lease_ready_flag = 1;
    run_rpc_lease();
  }
  c->flags |= C_REPARSE;
  assert (c->status != conn_wait_net);
}