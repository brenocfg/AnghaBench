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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  seed ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_FAST_PAC_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_MASTER_SECRET_LEN ; 
 int TLS_RANDOM_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sha1_t_prf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void eap_fast_derive_master_secret(const u8 *pac_key, const u8 *server_random,
				   const u8 *client_random, u8 *master_secret)
{
#define TLS_RANDOM_LEN 32
#define TLS_MASTER_SECRET_LEN 48
	u8 seed[2 * TLS_RANDOM_LEN];

	wpa_hexdump(MSG_DEBUG, "EAP-FAST: client_random",
		    client_random, TLS_RANDOM_LEN);
	wpa_hexdump(MSG_DEBUG, "EAP-FAST: server_random",
		    server_random, TLS_RANDOM_LEN);

	/*
	 * RFC 4851, Section 5.1:
	 * master_secret = T-PRF(PAC-Key, "PAC to master secret label hash",
	 *                       server_random + client_random, 48)
	 */
	os_memcpy(seed, server_random, TLS_RANDOM_LEN);
	os_memcpy(seed + TLS_RANDOM_LEN, client_random, TLS_RANDOM_LEN);
	sha1_t_prf(pac_key, EAP_FAST_PAC_KEY_LEN,
		   "PAC to master secret label hash",
		   seed, sizeof(seed), master_secret, TLS_MASTER_SECRET_LEN);

	wpa_hexdump_key(MSG_DEBUG, "EAP-FAST: master_secret",
			master_secret, TLS_MASTER_SECRET_LEN);
}