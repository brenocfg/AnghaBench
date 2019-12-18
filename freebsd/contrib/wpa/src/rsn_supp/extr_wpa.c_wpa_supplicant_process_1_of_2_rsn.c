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
typedef  int u8 ;
typedef  int u16 ;
struct wpa_sm {TYPE_1__* ctx; int /*<<< orphan*/  group_cipher; } ;
struct wpa_gtk_data {int gtk_len; int keyidx; int /*<<< orphan*/  gtk; int /*<<< orphan*/  tx; int /*<<< orphan*/  alg; int /*<<< orphan*/  key_rsc_len; } ;
struct wpa_eapol_ie_parse {int const* gtk; int gtk_len; int /*<<< orphan*/  oci_len; int /*<<< orphan*/  oci; } ;
struct wpa_channel_info {int /*<<< orphan*/  seg1_idx; int /*<<< orphan*/  chanwidth; } ;
struct TYPE_2__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int WPA_KEY_INFO_ENCR_KEY_DATA ; 
 int /*<<< orphan*/  channel_width_to_int (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211w_set_keys (struct wpa_sm*,struct wpa_eapol_ie_parse*) ; 
 int /*<<< orphan*/  ocv_errorstr ; 
 scalar_t__ ocv_verify_tx_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_channel_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_sm_channel_info (struct wpa_sm*,struct wpa_channel_info*) ; 
 scalar_t__ wpa_sm_ocv_enabled (struct wpa_sm*) ; 
 scalar_t__ wpa_supplicant_check_group_cipher (struct wpa_sm*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_gtk_tx_bit_workaround (struct wpa_sm*,int) ; 
 scalar_t__ wpa_supplicant_parse_ies (int const*,size_t,struct wpa_eapol_ie_parse*) ; 

__attribute__((used)) static int wpa_supplicant_process_1_of_2_rsn(struct wpa_sm *sm,
					     const u8 *keydata,
					     size_t keydatalen,
					     u16 key_info,
					     struct wpa_gtk_data *gd)
{
	int maxkeylen;
	struct wpa_eapol_ie_parse ie;

	wpa_hexdump_key(MSG_DEBUG, "RSN: msg 1/2 key data",
			keydata, keydatalen);
	if (wpa_supplicant_parse_ies(keydata, keydatalen, &ie) < 0)
		return -1;
	if (ie.gtk && !(key_info & WPA_KEY_INFO_ENCR_KEY_DATA)) {
		wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
			"WPA: GTK IE in unencrypted key data");
		return -1;
	}
	if (ie.gtk == NULL) {
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
			"WPA: No GTK IE in Group Key msg 1/2");
		return -1;
	}
	maxkeylen = gd->gtk_len = ie.gtk_len - 2;

#ifdef CONFIG_OCV
	if (wpa_sm_ocv_enabled(sm)) {
		struct wpa_channel_info ci;

		if (wpa_sm_channel_info(sm, &ci) != 0) {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"Failed to get channel info to validate received OCI in EAPOL-Key group msg 1/2");
			return -1;
		}

		if (ocv_verify_tx_params(ie.oci, ie.oci_len, &ci,
					 channel_width_to_int(ci.chanwidth),
					 ci.seg1_idx) != 0) {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING, "%s",
				ocv_errorstr);
			return -1;
		}
	}
#endif /* CONFIG_OCV */

	if (wpa_supplicant_check_group_cipher(sm, sm->group_cipher,
					      gd->gtk_len, maxkeylen,
					      &gd->key_rsc_len, &gd->alg))
		return -1;

	wpa_hexdump_key(MSG_DEBUG, "RSN: received GTK in group key handshake",
			ie.gtk, ie.gtk_len);
	gd->keyidx = ie.gtk[0] & 0x3;
	gd->tx = wpa_supplicant_gtk_tx_bit_workaround(sm,
						      !!(ie.gtk[0] & BIT(2)));
	if (ie.gtk_len - 2 > sizeof(gd->gtk)) {
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
			"RSN: Too long GTK in GTK IE (len=%lu)",
			(unsigned long) ie.gtk_len - 2);
		return -1;
	}
	os_memcpy(gd->gtk, ie.gtk + 2, ie.gtk_len - 2);

	if (ieee80211w_set_keys(sm, &ie) < 0)
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
			"RSN: Failed to configure IGTK");

	return 0;
}