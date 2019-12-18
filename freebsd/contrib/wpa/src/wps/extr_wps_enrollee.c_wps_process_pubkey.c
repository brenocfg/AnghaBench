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
typedef  int /*<<< orphan*/  const u8 ;
struct wps_data {int /*<<< orphan*/ * dh_pubkey_r; int /*<<< orphan*/  config_error; int /*<<< orphan*/  const* peer_pubkey_hash; scalar_t__ peer_pubkey_hash_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPS_CFG_PUBLIC_KEY_HASH_MISMATCH ; 
 int WPS_HASH_LEN ; 
 size_t WPS_OOB_PUBKEY_HASH_LEN ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_alloc_copy (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 scalar_t__ wps_derive_keys (struct wps_data*) ; 

__attribute__((used)) static int wps_process_pubkey(struct wps_data *wps, const u8 *pk,
			      size_t pk_len)
{
	if (pk == NULL || pk_len == 0) {
		wpa_printf(MSG_DEBUG, "WPS: No Public Key received");
		return -1;
	}

	if (wps->peer_pubkey_hash_set) {
		u8 hash[WPS_HASH_LEN];
		sha256_vector(1, &pk, &pk_len, hash);
		if (os_memcmp_const(hash, wps->peer_pubkey_hash,
				    WPS_OOB_PUBKEY_HASH_LEN) != 0) {
			wpa_printf(MSG_ERROR, "WPS: Public Key hash mismatch");
			wpa_hexdump(MSG_DEBUG, "WPS: Received public key",
				    pk, pk_len);
			wpa_hexdump(MSG_DEBUG, "WPS: Calculated public key "
				    "hash", hash, WPS_OOB_PUBKEY_HASH_LEN);
			wpa_hexdump(MSG_DEBUG, "WPS: Expected public key hash",
				    wps->peer_pubkey_hash,
				    WPS_OOB_PUBKEY_HASH_LEN);
			wps->config_error = WPS_CFG_PUBLIC_KEY_HASH_MISMATCH;
			return -1;
		}
	}

	wpabuf_free(wps->dh_pubkey_r);
	wps->dh_pubkey_r = wpabuf_alloc_copy(pk, pk_len);
	if (wps->dh_pubkey_r == NULL)
		return -1;

	if (wps_derive_keys(wps) < 0)
		return -1;

	return 0;
}