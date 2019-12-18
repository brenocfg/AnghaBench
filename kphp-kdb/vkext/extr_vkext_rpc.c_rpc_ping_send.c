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
struct rpc_server {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_PING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_write_long (int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  buffer_write_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outbuf ; 
 int rpc_flush_out_force (struct rpc_server*,double) ; 
 scalar_t__ rpc_write_handshake (struct rpc_server*,int /*<<< orphan*/ ,double) ; 

__attribute__((used)) static int rpc_ping_send (struct rpc_server *server, double timeout, long long value) { /* {{{ */
  assert (outbuf);
  buffer_clear (outbuf);
  buffer_write_reserve (outbuf, 12);
  buffer_write_long (outbuf, value);
  if (rpc_write_handshake (server, RPC_PING, timeout) < 0) {
    return -1;
  }
  return rpc_flush_out_force (server, timeout);
}