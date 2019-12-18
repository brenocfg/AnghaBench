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
struct rpc_join_ack {long long id; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 scalar_t__ Q ; 
 int /*<<< orphan*/  RPC_TYPE_JOIN_ACK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rpc_create_query (struct rpc_join_ack*,int,struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_query (struct rpc_join_ack*,struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpc_send_join_ack (struct connection *c, long long x) {
  if (verbosity >= 2) {
    fprintf (stderr, "rpc_send_join_ack\n");
  }
  struct rpc_join_ack *T = (struct rpc_join_ack *)Q;
  rpc_create_query (T, sizeof (struct rpc_join_ack), c, RPC_TYPE_JOIN_ACK);
  T->id = x;
  return rpc_send_query (T, c);
}