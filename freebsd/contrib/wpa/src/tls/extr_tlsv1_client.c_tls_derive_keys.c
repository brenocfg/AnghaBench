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
typedef  int /*<<< orphan*/  const u8 ;
struct TYPE_2__ {scalar_t__ tls_version; int hash_size; int key_material_len; int iv_size; int /*<<< orphan*/  const* write_iv; int /*<<< orphan*/  const* read_iv; int /*<<< orphan*/  const* read_key; int /*<<< orphan*/  const* write_key; int /*<<< orphan*/  const* read_mac_secret; int /*<<< orphan*/  const* write_mac_secret; } ;
struct tlsv1_client {TYPE_1__ rl; int /*<<< orphan*/  const* master_secret; int /*<<< orphan*/  const* client_random; int /*<<< orphan*/  const* server_random; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 size_t TLS_MASTER_SECRET_LEN ; 
 int TLS_MAX_KEY_BLOCK_LEN ; 
 int TLS_RANDOM_LEN ; 
 scalar_t__ TLS_VERSION_1 ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tls_prf (scalar_t__,int /*<<< orphan*/  const*,size_t,char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int tls_derive_keys(struct tlsv1_client *conn,
		    const u8 *pre_master_secret, size_t pre_master_secret_len)
{
	u8 seed[2 * TLS_RANDOM_LEN];
	u8 key_block[TLS_MAX_KEY_BLOCK_LEN];
	u8 *pos;
	size_t key_block_len;

	if (pre_master_secret) {
		wpa_hexdump_key(MSG_MSGDUMP, "TLSv1: pre_master_secret",
				pre_master_secret, pre_master_secret_len);
		os_memcpy(seed, conn->client_random, TLS_RANDOM_LEN);
		os_memcpy(seed + TLS_RANDOM_LEN, conn->server_random,
			  TLS_RANDOM_LEN);
		if (tls_prf(conn->rl.tls_version,
			    pre_master_secret, pre_master_secret_len,
			    "master secret", seed, 2 * TLS_RANDOM_LEN,
			    conn->master_secret, TLS_MASTER_SECRET_LEN)) {
			wpa_printf(MSG_DEBUG, "TLSv1: Failed to derive "
				   "master_secret");
			return -1;
		}
		wpa_hexdump_key(MSG_MSGDUMP, "TLSv1: master_secret",
				conn->master_secret, TLS_MASTER_SECRET_LEN);
	}

	os_memcpy(seed, conn->server_random, TLS_RANDOM_LEN);
	os_memcpy(seed + TLS_RANDOM_LEN, conn->client_random, TLS_RANDOM_LEN);
	key_block_len = 2 * (conn->rl.hash_size + conn->rl.key_material_len);
	if (conn->rl.tls_version == TLS_VERSION_1)
		key_block_len += 2 * conn->rl.iv_size;
	if (tls_prf(conn->rl.tls_version,
		    conn->master_secret, TLS_MASTER_SECRET_LEN,
		    "key expansion", seed, 2 * TLS_RANDOM_LEN,
		    key_block, key_block_len)) {
		wpa_printf(MSG_DEBUG, "TLSv1: Failed to derive key_block");
		return -1;
	}
	wpa_hexdump_key(MSG_MSGDUMP, "TLSv1: key_block",
			key_block, key_block_len);

	pos = key_block;

	/* client_write_MAC_secret */
	os_memcpy(conn->rl.write_mac_secret, pos, conn->rl.hash_size);
	pos += conn->rl.hash_size;
	/* server_write_MAC_secret */
	os_memcpy(conn->rl.read_mac_secret, pos, conn->rl.hash_size);
	pos += conn->rl.hash_size;

	/* client_write_key */
	os_memcpy(conn->rl.write_key, pos, conn->rl.key_material_len);
	pos += conn->rl.key_material_len;
	/* server_write_key */
	os_memcpy(conn->rl.read_key, pos, conn->rl.key_material_len);
	pos += conn->rl.key_material_len;

	if (conn->rl.tls_version == TLS_VERSION_1) {
		/* client_write_IV */
		os_memcpy(conn->rl.write_iv, pos, conn->rl.iv_size);
		pos += conn->rl.iv_size;
		/* server_write_IV */
		os_memcpy(conn->rl.read_iv, pos, conn->rl.iv_size);
	} else {
		/*
		 * Use IV field to set the mask value for TLS v1.1. A fixed
		 * mask of zero is used per the RFC 4346, 6.2.3.2 CBC Block
		 * Cipher option 2a.
		 */
		os_memset(conn->rl.write_iv, 0, conn->rl.iv_size);
	}

	return 0;
}