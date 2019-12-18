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
struct rpcc_op {int /*<<< orphan*/  id; } ;
struct rpc_request_update_stats {int dummy; } ;
struct rpc_kicked {int dummy; } ;
struct rpc_join_ack {int dummy; } ;
struct rpc_delays {int dummy; } ;
struct rpc_children_answer {int dummy; } ;
struct connection {int fd; int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int MAX_PACKET_LEN ; 
 scalar_t__ P ; 
#define  RPC_TYPE_CHILDREN_ANSWER 132 
#define  RPC_TYPE_DELAYS 131 
#define  RPC_TYPE_JOIN_ACK 130 
#define  RPC_TYPE_KICKED 129 
#define  RPC_TYPE_REQUEST_UPDATE_STATS 128 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ choose_cluster (int /*<<< orphan*/ ) ; 
 scalar_t__ choose_cluster_f (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int read_in (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int rpc_check_crc32 (scalar_t__) ; 
 int rpc_execute_children_answer (struct connection*,struct rpc_children_answer*,int) ; 
 int rpc_execute_delays (struct connection*,struct rpc_delays*,int) ; 
 int rpc_execute_join_ack (struct connection*,struct rpc_join_ack*,int) ; 
 int rpc_execute_kicked (struct connection*,struct rpc_kicked*,int) ; 
 int rpc_execute_request_update_stats (struct connection*,struct rpc_request_update_stats*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int rpcc_execute (struct connection *c, int op, int len) {
  if (verbosity > 1) {
    fprintf (stderr, "rpcc_execute: fd=%d, op=%x, len=%d\n", c->fd, op, len);
  }
  if (len > MAX_PACKET_LEN) {
    return SKIP_ALL_BYTES;    
  }

  assert (read_in (&c->In, &P, len) == len);
  assert (rpc_check_crc32 (P));
  

  if ((op != RPC_TYPE_JOIN_ACK || choose_cluster_f (((struct rpcc_op *)P)->id) < 0) && choose_cluster (((struct rpcc_op *)P)->id) < 0) {
    return 0;
  }

  vkprintf (6, "%x\n", op);

  switch (op) {
  case RPC_TYPE_JOIN_ACK:
    return rpc_execute_join_ack (c, (struct rpc_join_ack *)P, len);
  case RPC_TYPE_CHILDREN_ANSWER:
    return rpc_execute_children_answer (c, (struct rpc_children_answer *)P, len);
  case RPC_TYPE_KICKED:
    return rpc_execute_kicked (c, (struct rpc_kicked *)P, len);
  case RPC_TYPE_REQUEST_UPDATE_STATS:
    return rpc_execute_request_update_stats (c, (struct rpc_request_update_stats *)P, len);
  case RPC_TYPE_DELAYS:
    return rpc_execute_delays (c, (struct rpc_delays *)P, len);
  }
  return 0;
}