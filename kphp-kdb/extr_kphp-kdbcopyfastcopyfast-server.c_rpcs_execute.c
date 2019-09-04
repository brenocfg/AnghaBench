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
struct rpc_update_stats {int dummy; } ;
struct rpc_stats {int dummy; } ;
struct rpc_join_old {int dummy; } ;
struct rpc_join {int dummy; } ;
struct rpc_children_request {int dummy; } ;
struct connection {int fd; int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int MAX_PACKET_LEN ; 
 scalar_t__ P ; 
#define  RPC_TYPE_CHILDREN_REQUEST 132 
#define  RPC_TYPE_JOIN 131 
#define  RPC_TYPE_JOIN_OLD 130 
#define  RPC_TYPE_STATS 129 
#define  RPC_TYPE_UPDATE_STATS 128 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int read_in (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int rpc_check_crc32 (scalar_t__) ; 
 int rpc_execute_children_request (struct connection*,struct rpc_children_request*,int) ; 
 int rpc_execute_join (struct connection*,struct rpc_join*,int) ; 
 int rpc_execute_join_old (struct connection*,struct rpc_join_old*,int) ; 
 int rpc_execute_stats (struct connection*,struct rpc_stats*,int) ; 
 int rpc_execute_update_stats (struct connection*,struct rpc_update_stats*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int rpcs_execute (struct connection *c, int op, int len) {
  if (verbosity > 0) {
    fprintf (stderr, "rpcs_execute: fd=%d, op=%x, len=%d\n", c->fd, op, len);
  }
  if (len > MAX_PACKET_LEN) {
    return SKIP_ALL_BYTES;    
  }

  assert (read_in (&c->In, &P, len) == len);
  assert (rpc_check_crc32 (P));


  switch (op) {
  case RPC_TYPE_JOIN:
    return rpc_execute_join (c, (struct rpc_join *)P, len);
    break;

  case RPC_TYPE_JOIN_OLD:
    return rpc_execute_join_old (c, (struct rpc_join_old *)P, len);
    break;

  case RPC_TYPE_CHILDREN_REQUEST:
    return rpc_execute_children_request (c, (struct rpc_children_request *)P, len);
    break;

  case RPC_TYPE_STATS:
    return rpc_execute_stats (c, (struct rpc_stats *)P, len);
    break;

  case RPC_TYPE_UPDATE_STATS:
    return rpc_execute_update_stats (c, (struct rpc_update_stats *)P, len);
    break;
  }
  return 0;
}