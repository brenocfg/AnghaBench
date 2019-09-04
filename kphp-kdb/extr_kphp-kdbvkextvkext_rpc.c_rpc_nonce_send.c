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
struct rpc_nonce {int /*<<< orphan*/  crypto_schema; int /*<<< orphan*/  key_select; } ;
typedef  int /*<<< orphan*/  S ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_NONCE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_write_data (int /*<<< orphan*/ ,struct rpc_nonce*,int) ; 
 int /*<<< orphan*/  buffer_write_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outbuf ; 
 int rpc_flush_out_force (struct rpc_server*,double) ; 
 scalar_t__ rpc_write_handshake (struct rpc_server*,int /*<<< orphan*/ ,double) ; 

__attribute__((used)) static int rpc_nonce_send (struct rpc_server *server, double timeout) { /* {{{ */
  struct rpc_nonce S = {
    .key_select = 0,
    .crypto_schema = 0
  };
  
  //server->outbuf = buffer_create (sizeof (S));
  assert (outbuf);
  buffer_clear (outbuf);
  buffer_write_reserve (outbuf, 12);
  buffer_write_data (outbuf, &S, sizeof (S));
  if (rpc_write_handshake (server, RPC_NONCE, timeout) < 0) {
    return -1;
  }
  return rpc_flush_out_force (server, timeout);
}