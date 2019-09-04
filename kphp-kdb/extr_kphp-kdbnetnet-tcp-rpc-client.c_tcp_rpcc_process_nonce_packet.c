#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcp_rpc_nonce_packet {int crypto_schema; int /*<<< orphan*/  key_select; int /*<<< orphan*/  crypto_nonce; scalar_t__ crypto_ts; } ;
struct tcp_rpc_data {int packet_num; scalar_t__ packet_type; int packet_len; int crypto_flags; scalar_t__ nonce_time; } ;
struct raw_message {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  total_bytes; } ;
struct connection {TYPE_1__ out_p; } ;
struct TYPE_4__ {int (* rpc_start_crypto ) (struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  RPC_CRYPTO_AES 129 
#define  RPC_CRYPTO_NONE 128 
 scalar_t__ RPC_NONCE ; 
 TYPE_2__* TCP_RPCC_FUNC (struct connection*) ; 
 struct tcp_rpc_data* TCP_RPC_DATA (struct connection*) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_crypto_key_id () ; 
 int rwm_fetch_data (struct raw_message*,struct tcp_rpc_nonce_packet*,int) ; 
 int stub1 (struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,...) ; 

__attribute__((used)) static int tcp_rpcc_process_nonce_packet (struct connection *c, struct raw_message *msg) {
  struct tcp_rpc_data *D = TCP_RPC_DATA(c);
  static struct tcp_rpc_nonce_packet P;
  int res;

  if (D->packet_num != -2 || D->packet_type != RPC_NONCE) {
    return -2;
  }
  if (D->packet_len != sizeof (struct tcp_rpc_nonce_packet)) {
    return -3;
  }

  assert (rwm_fetch_data (msg, &P, D->packet_len) == D->packet_len);

  vkprintf (2, "Processing nonce packet, crypto schema: %d, key select: %d\n", P.crypto_schema, P.key_select);

  switch (P.crypto_schema) {
  case RPC_CRYPTO_NONE:
    if (P.key_select) {
      return -3;
    }
    if (D->crypto_flags & 1) {
      if (D->crypto_flags & 2) {
        assert (!c->out_p.total_bytes);
      }
      D->crypto_flags = 1;
    } else {
      return -5;
    }
    break;
  case RPC_CRYPTO_AES:
    if (!P.key_select || P.key_select != get_crypto_key_id ()) {
      return -3;
    }
    if (!(D->crypto_flags & 2)) {
      return -5;
    }
    if (abs (P.crypto_ts - D->nonce_time) > 30) {
      return -6;        //less'om
    }
    res = TCP_RPCC_FUNC(c)->rpc_start_crypto (c, P.crypto_nonce, P.key_select);
    if (res < 0) {
      return -6;
    }
    break;
  default:
    return -4;
  }
  vkprintf (2, "Processed nonce packet, crypto flags = %d\n", D->crypto_flags);
  return 0;
}