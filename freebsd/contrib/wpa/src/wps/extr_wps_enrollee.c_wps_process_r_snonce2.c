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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;
struct wps_data {TYPE_1__ peer_dev; int /*<<< orphan*/  wps; int /*<<< orphan*/  config_error; int /*<<< orphan*/  peer_hash2; int /*<<< orphan*/  authkey; int /*<<< orphan*/  dh_pubkey_r; int /*<<< orphan*/  dh_pubkey_e; int /*<<< orphan*/ * psk2; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  WPS_AUTHKEY_LEN ; 
 int /*<<< orphan*/  WPS_CFG_DEV_PASSWORD_AUTH_FAILURE ; 
 int /*<<< orphan*/  WPS_HASH_LEN ; 
 size_t WPS_PSK_LEN ; 
 size_t WPS_SECRET_NONCE_LEN ; 
 int /*<<< orphan*/  hmac_sha256_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_head (int /*<<< orphan*/ ) ; 
 size_t wpabuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_pwd_auth_fail_event (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_process_r_snonce2(struct wps_data *wps, const u8 *r_snonce2)
{
	u8 hash[SHA256_MAC_LEN];
	const u8 *addr[4];
	size_t len[4];

	if (r_snonce2 == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: No R-SNonce2 received");
		return -1;
	}

	wpa_hexdump_key(MSG_DEBUG, "WPS: R-SNonce2", r_snonce2,
			WPS_SECRET_NONCE_LEN);

	/* R-Hash2 = HMAC_AuthKey(R-S2 || PSK2 || PK_E || PK_R) */
	addr[0] = r_snonce2;
	len[0] = WPS_SECRET_NONCE_LEN;
	addr[1] = wps->psk2;
	len[1] = WPS_PSK_LEN;
	addr[2] = wpabuf_head(wps->dh_pubkey_e);
	len[2] = wpabuf_len(wps->dh_pubkey_e);
	addr[3] = wpabuf_head(wps->dh_pubkey_r);
	len[3] = wpabuf_len(wps->dh_pubkey_r);
	hmac_sha256_vector(wps->authkey, WPS_AUTHKEY_LEN, 4, addr, len, hash);

	if (os_memcmp_const(wps->peer_hash2, hash, WPS_HASH_LEN) != 0) {
		wpa_printf(MSG_DEBUG, "WPS: R-Hash2 derived from R-S2 does "
			   "not match with the pre-committed value");
		wps->config_error = WPS_CFG_DEV_PASSWORD_AUTH_FAILURE;
		wps_pwd_auth_fail_event(wps->wps, 1, 2, wps->peer_dev.mac_addr);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "WPS: Registrar proved knowledge of the second "
		   "half of the device password");

	return 0;
}