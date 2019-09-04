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
struct copyexec_rpc_send_data {int dummy; } ;
struct copyexec_rpc_handshake {int dummy; } ;
struct connection {int /*<<< orphan*/  In; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
#define  COPYEXEC_RPC_TYPE_HANDSHAKE 130 
#define  COPYEXEC_RPC_TYPE_PING 129 
#define  COPYEXEC_RPC_TYPE_SEND_DATA 128 
 int MAX_PACKET_LEN ; 
 int /*<<< orphan*/  P ; 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int read_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int rpc_execute_handshake (struct connection*,struct copyexec_rpc_handshake*,int) ; 
 int rpc_execute_ping (struct connection*) ; 
 int rpc_execute_send_data (struct connection*,struct copyexec_rpc_send_data*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int,int) ; 

int rpcs_execute (struct connection *c, int op, int len) {
  vkprintf (3, "rpcs_execute: fd=%d, op=%x, len=%d\n", c->fd, op, len);

  if (len > MAX_PACKET_LEN) {
    return SKIP_ALL_BYTES;
  }

  assert (read_in (&c->In, &P, len) == len);
  len -= 16;
  switch (op) {
    case COPYEXEC_RPC_TYPE_HANDSHAKE:
      return rpc_execute_handshake (c, (struct copyexec_rpc_handshake *) (P + 3), len);
    case COPYEXEC_RPC_TYPE_SEND_DATA:
      return rpc_execute_send_data (c, (struct copyexec_rpc_send_data *) (P + 3), len);
    case COPYEXEC_RPC_TYPE_PING:
      return rpc_execute_ping (c);
  }

  return -__LINE__;
}