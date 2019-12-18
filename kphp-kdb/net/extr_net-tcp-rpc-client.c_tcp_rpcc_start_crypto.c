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
struct tcp_rpc_data {int /*<<< orphan*/  nonce_time; int /*<<< orphan*/  nonce; } ;
struct TYPE_4__ {scalar_t__ total_bytes; } ;
struct TYPE_3__ {scalar_t__ total_bytes; } ;
struct connection {int /*<<< orphan*/  our_ipv6; int /*<<< orphan*/  our_port; int /*<<< orphan*/  our_ip; int /*<<< orphan*/  remote_ipv6; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  remote_ip; TYPE_2__ out; TYPE_1__ in; scalar_t__ crypto; } ;
struct aes_key_data {int dummy; } ;
typedef  int /*<<< orphan*/  aes_keys ;

/* Variables and functions */
 struct tcp_rpc_data* TCP_RPC_DATA (struct connection*) ; 
 scalar_t__ aes_create_keys (struct aes_key_data*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ aes_crypto_init (struct connection*,struct aes_key_data*,int) ; 
 int get_crypto_key_id () ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int tcp_rpcc_start_crypto (struct connection *c, char *nonce, int key_select) {
  struct tcp_rpc_data *D = TCP_RPC_DATA(c);

  vkprintf (2, "rpcc_start_crypto: key_select = %d\n", key_select);

  if (c->crypto) {
    return -1;
  }

  if (c->in.total_bytes || c->out.total_bytes || !D->nonce_time) {
    return -1;
  }

  if (!key_select || key_select != get_crypto_key_id ()) {
    return -1;
  }

  struct aes_key_data aes_keys;

  if (aes_create_keys (&aes_keys, 1, nonce, D->nonce, D->nonce_time, c->remote_ip, c->remote_port, c->remote_ipv6, c->our_ip, c->our_port, c->our_ipv6) < 0) {
    return -1;
  }

  if (aes_crypto_init (c, &aes_keys, sizeof (aes_keys)) < 0) {
    return -1;
  }

  return 1;
}