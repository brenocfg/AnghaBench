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
struct rpcs_op {int remote_id; } ;
struct rpc_handshake_reject {int dummy; } ;
struct rpc_handshake_accept {int dummy; } ;
struct rpc_handshake {int dummy; } ;
struct rpc_binlog_request {int dummy; } ;
struct rpc_binlog_info {int dummy; } ;
struct rpc_binlog_data {int dummy; } ;
struct connection {int fd; int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int CLUSTER_MASK ; 
 int MAX_PACKET_LEN ; 
 int NODE_ID ; 
 scalar_t__ P ; 
#define  RPC_TYPE_BINLOG_DATA 133 
#define  RPC_TYPE_BINLOG_INFO 132 
#define  RPC_TYPE_BINLOG_REQUEST 131 
#define  RPC_TYPE_HANDSHAKE 130 
#define  RPC_TYPE_HANDSHAKE_ACCEPT 129 
#define  RPC_TYPE_HANDSHAKE_REJECT 128 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ choose_cluster (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int read_in (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int rpc_check_crc32 (scalar_t__) ; 
 int rpc_execute_binlog_data (struct connection*,struct rpc_binlog_data*,int) ; 
 int rpc_execute_binlog_info (struct connection*,struct rpc_binlog_info*,int) ; 
 int rpc_execute_binlog_request (struct connection*,struct rpc_binlog_request*,int) ; 
 int rpc_execute_handshake (struct connection*,struct rpc_handshake*,int) ; 
 int rpc_execute_handshake_accept (struct connection*,struct rpc_handshake_accept*,int) ; 
 int rpc_execute_handshake_reject (struct connection*,struct rpc_handshake_reject*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpcs_execute (struct connection *c, int op, int len) {
  if (verbosity > 1) {
    fprintf (stderr, "rpcs_execute: fd=%d, op=%x, len=%d\n", c->fd, op, len);
  }
  if (len > MAX_PACKET_LEN) {
    return SKIP_ALL_BYTES;    
  }

  assert (read_in (&c->In, &P, len) == len);
  assert (rpc_check_crc32 (P));

  if (choose_cluster (((struct rpcs_op *)P)->remote_id) < 0 || (((struct rpcs_op *)P)->remote_id & CLUSTER_MASK) != (NODE_ID & CLUSTER_MASK)) {
    return 0;
  }

  switch (op) {
  case RPC_TYPE_HANDSHAKE:
    return rpc_execute_handshake (c, (struct rpc_handshake *)P, len);
  case RPC_TYPE_HANDSHAKE_ACCEPT:
    return rpc_execute_handshake_accept (c, (struct rpc_handshake_accept *)P, len);
  case RPC_TYPE_HANDSHAKE_REJECT:
    return rpc_execute_handshake_reject (c, (struct rpc_handshake_reject *)P, len);
  case RPC_TYPE_BINLOG_INFO:
    return rpc_execute_binlog_info (c, (struct rpc_binlog_info *)P, len);
  case RPC_TYPE_BINLOG_REQUEST:
    return rpc_execute_binlog_request (c, (struct rpc_binlog_request *)P, len);
  case RPC_TYPE_BINLOG_DATA:
    return rpc_execute_binlog_data (c, (struct rpc_binlog_data *)P, len);
  //case RPC_TYPE_DIVORCE:
  //  return rpc_execute_divorce (c, (struct rpc_divorce *)P, len);
  }

  return 0;
}