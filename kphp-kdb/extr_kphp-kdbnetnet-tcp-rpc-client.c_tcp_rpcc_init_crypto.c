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
struct tcp_rpc_nonce_packet {int /*<<< orphan*/  crypto_schema; int /*<<< orphan*/  key_select; int /*<<< orphan*/  type; int /*<<< orphan*/  crypto_ts; int /*<<< orphan*/  crypto_nonce; } ;
struct connection {int /*<<< orphan*/  crypto; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int crypto_flags; int /*<<< orphan*/  nonce_time; int /*<<< orphan*/  nonce; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_CRYPTO_AES ; 
 int /*<<< orphan*/  RPC_NONCE ; 
 TYPE_1__* TCP_RPC_DATA (struct connection*) ; 
 int /*<<< orphan*/  aes_generate_nonce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_crypto_key_id () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct tcp_rpc_nonce_packet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_rpc_conn_send_data (struct connection*,int,struct tcp_rpc_nonce_packet*) ; 
 int tcp_rpcc_init_fake_crypto (struct connection*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

int tcp_rpcc_init_crypto (struct connection *c) {
  if (!(TCP_RPC_DATA(c)->crypto_flags & 2)) {
    return tcp_rpcc_init_fake_crypto (c);
  }

  TCP_RPC_DATA(c)->nonce_time = time (0);

  aes_generate_nonce (TCP_RPC_DATA(c)->nonce);

  static struct tcp_rpc_nonce_packet buf;
  memset (&buf, 0, sizeof (buf));
  memcpy (buf.crypto_nonce, TCP_RPC_DATA(c)->nonce, 16);
  buf.crypto_ts = TCP_RPC_DATA(c)->nonce_time;
  buf.type = RPC_NONCE;
  buf.key_select = get_crypto_key_id ();
  buf.crypto_schema = RPC_CRYPTO_AES;

  tcp_rpc_conn_send_data (c, sizeof (buf), &buf);

  assert ((TCP_RPC_DATA(c)->crypto_flags & 14) == 2);
  TCP_RPC_DATA(c)->crypto_flags |= 4;

  assert (!c->crypto);

/*  struct raw_message x;
  assert (!c->out_p.total_bytes);
  x = c->out_p;
  c->out_p = c->out;
  c->out = x;*/

  return 1;
}