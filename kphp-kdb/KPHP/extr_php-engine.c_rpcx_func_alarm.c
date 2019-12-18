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
struct connection {scalar_t__ status; } ;
typedef  int /*<<< orphan*/  php_worker ;

/* Variables and functions */
 struct rpcs_data* RPCS_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_expect_query ; 
 scalar_t__ conn_wait_net ; 
 int php_worker_main (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_worker_terminate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rpcx_at_query_end (struct connection*) ; 

int rpcx_func_alarm (struct connection *c) {
  struct rpcs_data *D = RPCS_DATA(c);

  //fprintf (stderr, "pending_queries = %d\n", c->pending_queries);

  assert (c->status == conn_expect_query || c->status == conn_wait_net);
  c->status = conn_expect_query;

  php_worker *worker = D->extra;
  php_worker_terminate (worker, 0, "rpc connection alarm");
  int res = php_worker_main (worker);
  if (res == 1) {
    rpcx_at_query_end (c);
  } else {
    assert ("worker is unfinished after alarm" && 0);
  }
  return 0;
}