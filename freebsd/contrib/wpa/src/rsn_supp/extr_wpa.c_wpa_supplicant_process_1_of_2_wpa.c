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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct TYPE_3__ {int kek_len; int /*<<< orphan*/  const* kek; } ;
struct wpa_sm {TYPE_2__* ctx; TYPE_1__ ptk; int /*<<< orphan*/  group_cipher; } ;
struct wpa_gtk_data {size_t gtk_len; size_t keyidx; int /*<<< orphan*/  tx; int /*<<< orphan*/ * gtk; int /*<<< orphan*/  alg; int /*<<< orphan*/  key_rsc_len; } ;
struct wpa_eapol_key {int /*<<< orphan*/  const* key_iv; int /*<<< orphan*/  key_length; } ;
typedef  int /*<<< orphan*/  ek ;
struct TYPE_4__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 size_t WPA_GET_BE16 (int /*<<< orphan*/ ) ; 
 size_t WPA_KEY_INFO_KEY_INDEX_MASK ; 
 size_t WPA_KEY_INFO_KEY_INDEX_SHIFT ; 
 size_t WPA_KEY_INFO_TXRX ; 
 size_t WPA_KEY_INFO_TYPE_HMAC_MD5_RC4 ; 
 size_t WPA_KEY_INFO_TYPE_HMAC_SHA1_AES ; 
 scalar_t__ aes_unwrap (int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ rc4_skip (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_supplicant_check_group_cipher (struct wpa_sm*,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_gtk_tx_bit_workaround (struct wpa_sm*,int) ; 

__attribute__((used)) static int wpa_supplicant_process_1_of_2_wpa(struct wpa_sm *sm,
					     const struct wpa_eapol_key *key,
					     const u8 *key_data,
					     size_t key_data_len, u16 key_info,
					     u16 ver, struct wpa_gtk_data *gd)
{
	size_t maxkeylen;
	u16 gtk_len;

	gtk_len = WPA_GET_BE16(key->key_length);
	maxkeylen = key_data_len;
	if (ver == WPA_KEY_INFO_TYPE_HMAC_SHA1_AES) {
		if (maxkeylen < 8) {
			wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
				"WPA: Too short maxkeylen (%lu)",
				(unsigned long) maxkeylen);
			return -1;
		}
		maxkeylen -= 8;
	}

	if (gtk_len > maxkeylen ||
	    wpa_supplicant_check_group_cipher(sm, sm->group_cipher,
					      gtk_len, maxkeylen,
					      &gd->key_rsc_len, &gd->alg))
		return -1;

	gd->gtk_len = gtk_len;
	gd->keyidx = (key_info & WPA_KEY_INFO_KEY_INDEX_MASK) >>
		WPA_KEY_INFO_KEY_INDEX_SHIFT;
	if (ver == WPA_KEY_INFO_TYPE_HMAC_MD5_RC4 && sm->ptk.kek_len == 16) {
#ifdef CONFIG_NO_RC4
		wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
			"WPA: RC4 not supported in the build");
		return -1;
#else /* CONFIG_NO_RC4 */
		u8 ek[32];
		if (key_data_len > sizeof(gd->gtk)) {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"WPA: RC4 key data too long (%lu)",
				(unsigned long) key_data_len);
			return -1;
		}
		os_memcpy(ek, key->key_iv, 16);
		os_memcpy(ek + 16, sm->ptk.kek, sm->ptk.kek_len);
		os_memcpy(gd->gtk, key_data, key_data_len);
		if (rc4_skip(ek, 32, 256, gd->gtk, key_data_len)) {
			forced_memzero(ek, sizeof(ek));
			wpa_msg(sm->ctx->msg_ctx, MSG_ERROR,
				"WPA: RC4 failed");
			return -1;
		}
		forced_memzero(ek, sizeof(ek));
#endif /* CONFIG_NO_RC4 */
	} else if (ver == WPA_KEY_INFO_TYPE_HMAC_SHA1_AES) {
		if (maxkeylen % 8) {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"WPA: Unsupported AES-WRAP len %lu",
				(unsigned long) maxkeylen);
			return -1;
		}
		if (maxkeylen > sizeof(gd->gtk)) {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"WPA: AES-WRAP key data "
				"too long (keydatalen=%lu maxkeylen=%lu)",
				(unsigned long) key_data_len,
				(unsigned long) maxkeylen);
			return -1;
		}
		if (aes_unwrap(sm->ptk.kek, sm->ptk.kek_len, maxkeylen / 8,
			       key_data, gd->gtk)) {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"WPA: AES unwrap failed - could not decrypt "
				"GTK");
			return -1;
		}
	} else {
		wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
			"WPA: Unsupported key_info type %d", ver);
		return -1;
	}
	gd->tx = wpa_supplicant_gtk_tx_bit_workaround(
		sm, !!(key_info & WPA_KEY_INFO_TXRX));
	return 0;
}