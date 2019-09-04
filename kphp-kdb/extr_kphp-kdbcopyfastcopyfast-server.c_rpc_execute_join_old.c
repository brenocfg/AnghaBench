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
struct rpc_join_old {int /*<<< orphan*/  binlog_position; int /*<<< orphan*/  id; int /*<<< orphan*/  port; scalar_t__ host; } ;
struct connection {scalar_t__ remote_ip; } ;

/* Variables and functions */
 long long add_node (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int rpc_send_delays_old (struct connection*) ; 
 scalar_t__ rpc_send_join_ack (struct connection*,long long) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpc_execute_join_old (struct connection *c, struct rpc_join_old *P, int len) {
  if (verbosity >= 2) {
    fprintf (stderr, "rpc_execute_join_old: len = %d\n", len);
  }
  if (len != sizeof (struct rpc_join_old)) {
    return 0;
  }
  long long x = add_node (P->host ? P->host : c->remote_ip, P->port, P->id, P->binlog_position, c, 0);
  if (rpc_send_join_ack (c, x) < 0) {
    return -1;
  }
  return rpc_send_delays_old (c);
}