#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcp_rpc_nonce_packet {int /*<<< orphan*/  crypto_schema; int /*<<< orphan*/  type; } ;
struct connection {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int crypto_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_CRYPTO_NONE ; 
 int /*<<< orphan*/  RPC_NONCE ; 
 TYPE_1__* TCP_RPC_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (struct tcp_rpc_nonce_packet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_rpc_conn_send_data (struct connection*,int,struct tcp_rpc_nonce_packet*) ; 

int tcp_rpcc_init_fake_crypto (struct connection *c) {
  if (!(TCP_RPC_DATA(c)->crypto_flags & 1)) {
    return -1;
  }

  static struct tcp_rpc_nonce_packet buf;
  memset (&buf, 0, sizeof (buf));
  buf.type = RPC_NONCE;
  buf.crypto_schema = RPC_CRYPTO_NONE;

  tcp_rpc_conn_send_data (c, sizeof (buf), &buf);

  assert ((TCP_RPC_DATA(c)->crypto_flags & 14) == 0);
  TCP_RPC_DATA(c)->crypto_flags |= 4;
 
  return 1;
}