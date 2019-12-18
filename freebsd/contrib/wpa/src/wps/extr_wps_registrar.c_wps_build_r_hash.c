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
struct wps_data {int /*<<< orphan*/  authkey; int /*<<< orphan*/ * psk2; int /*<<< orphan*/ * snonce; int /*<<< orphan*/ * dh_pubkey_r; int /*<<< orphan*/ * dh_pubkey_e; int /*<<< orphan*/ * psk1; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int ATTR_R_HASH1 ; 
 int ATTR_R_HASH2 ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  WPS_AUTHKEY_LEN ; 
 size_t WPS_PSK_LEN ; 
 int WPS_SECRET_NONCE_LEN ; 
 int /*<<< orphan*/  hmac_sha256_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_head (int /*<<< orphan*/ *) ; 
 size_t wpabuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 

__attribute__((used)) static int wps_build_r_hash(struct wps_data *wps, struct wpabuf *msg)
{
	u8 *hash;
	const u8 *addr[4];
	size_t len[4];

	if (random_get_bytes(wps->snonce, 2 * WPS_SECRET_NONCE_LEN) < 0)
		return -1;
	wpa_hexdump(MSG_DEBUG, "WPS: R-S1", wps->snonce, WPS_SECRET_NONCE_LEN);
	wpa_hexdump(MSG_DEBUG, "WPS: R-S2",
		    wps->snonce + WPS_SECRET_NONCE_LEN, WPS_SECRET_NONCE_LEN);

	if (wps->dh_pubkey_e == NULL || wps->dh_pubkey_r == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: DH public keys not available for "
			   "R-Hash derivation");
		return -1;
	}

	wpa_printf(MSG_DEBUG, "WPS:  * R-Hash1");
	wpabuf_put_be16(msg, ATTR_R_HASH1);
	wpabuf_put_be16(msg, SHA256_MAC_LEN);
	hash = wpabuf_put(msg, SHA256_MAC_LEN);
	/* R-Hash1 = HMAC_AuthKey(R-S1 || PSK1 || PK_E || PK_R) */
	addr[0] = wps->snonce;
	len[0] = WPS_SECRET_NONCE_LEN;
	addr[1] = wps->psk1;
	len[1] = WPS_PSK_LEN;
	addr[2] = wpabuf_head(wps->dh_pubkey_e);
	len[2] = wpabuf_len(wps->dh_pubkey_e);
	addr[3] = wpabuf_head(wps->dh_pubkey_r);
	len[3] = wpabuf_len(wps->dh_pubkey_r);
	hmac_sha256_vector(wps->authkey, WPS_AUTHKEY_LEN, 4, addr, len, hash);
	wpa_hexdump(MSG_DEBUG, "WPS: R-Hash1", hash, SHA256_MAC_LEN);

	wpa_printf(MSG_DEBUG, "WPS:  * R-Hash2");
	wpabuf_put_be16(msg, ATTR_R_HASH2);
	wpabuf_put_be16(msg, SHA256_MAC_LEN);
	hash = wpabuf_put(msg, SHA256_MAC_LEN);
	/* R-Hash2 = HMAC_AuthKey(R-S2 || PSK2 || PK_E || PK_R) */
	addr[0] = wps->snonce + WPS_SECRET_NONCE_LEN;
	addr[1] = wps->psk2;
	hmac_sha256_vector(wps->authkey, WPS_AUTHKEY_LEN, 4, addr, len, hash);
	wpa_hexdump(MSG_DEBUG, "WPS: R-Hash2", hash, SHA256_MAC_LEN);

	return 0;
}