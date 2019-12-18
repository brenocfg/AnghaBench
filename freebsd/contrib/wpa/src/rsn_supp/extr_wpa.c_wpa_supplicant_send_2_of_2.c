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
typedef  int u16 ;
struct wpa_sm {scalar_t__ proto; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ptk; TYPE_1__* ctx; int /*<<< orphan*/  pmk_len; int /*<<< orphan*/  key_mgmt; } ;
struct wpa_eapol_key {int /*<<< orphan*/ * replay_counter; int /*<<< orphan*/ * key_length; int /*<<< orphan*/ * key_info; int /*<<< orphan*/  type; } ;
struct wpa_channel_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAPOL_KEY_TYPE_RSN ; 
 int /*<<< orphan*/  EAPOL_KEY_TYPE_WPA ; 
 int /*<<< orphan*/  ETH_P_EAPOL ; 
 int /*<<< orphan*/  IEEE802_1X_TYPE_EAPOL_KEY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 size_t OCV_OCI_KDE_LEN ; 
 int WPA_KEY_INFO_ENCR_KEY_DATA ; 
 int WPA_KEY_INFO_KEY_INDEX_MASK ; 
 int WPA_KEY_INFO_MIC ; 
 int WPA_KEY_INFO_SECURE ; 
 scalar_t__ WPA_PROTO_OSEN ; 
 scalar_t__ WPA_PROTO_RSN ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,size_t) ; 
 int WPA_REPLAY_COUNTER_LEN ; 
 scalar_t__ ocv_insert_oci_kde (struct wpa_channel_info*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int wpa_eapol_key_send (struct wpa_sm*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 size_t wpa_mic_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpa_sm_alloc_eapol (struct wpa_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t*,void*) ; 
 scalar_t__ wpa_sm_channel_info (struct wpa_sm*,struct wpa_channel_info*) ; 
 scalar_t__ wpa_sm_ocv_enabled (struct wpa_sm*) ; 

__attribute__((used)) static int wpa_supplicant_send_2_of_2(struct wpa_sm *sm,
				      const struct wpa_eapol_key *key,
				      int ver, u16 key_info)
{
	size_t mic_len, hdrlen, rlen;
	struct wpa_eapol_key *reply;
	u8 *rbuf, *key_mic;
	size_t kde_len = 0;

#ifdef CONFIG_OCV
	if (wpa_sm_ocv_enabled(sm))
		kde_len = OCV_OCI_KDE_LEN;
#endif /* CONFIG_OCV */

	mic_len = wpa_mic_len(sm->key_mgmt, sm->pmk_len);
	hdrlen = sizeof(*reply) + mic_len + 2;
	rbuf = wpa_sm_alloc_eapol(sm, IEEE802_1X_TYPE_EAPOL_KEY, NULL,
				  hdrlen + kde_len, &rlen, (void *) &reply);
	if (rbuf == NULL)
		return -1;

	reply->type = (sm->proto == WPA_PROTO_RSN ||
		       sm->proto == WPA_PROTO_OSEN) ?
		EAPOL_KEY_TYPE_RSN : EAPOL_KEY_TYPE_WPA;
	key_info &= WPA_KEY_INFO_KEY_INDEX_MASK;
	key_info |= ver | WPA_KEY_INFO_SECURE;
	if (mic_len)
		key_info |= WPA_KEY_INFO_MIC;
	else
		key_info |= WPA_KEY_INFO_ENCR_KEY_DATA;
	WPA_PUT_BE16(reply->key_info, key_info);
	if (sm->proto == WPA_PROTO_RSN || sm->proto == WPA_PROTO_OSEN)
		WPA_PUT_BE16(reply->key_length, 0);
	else
		os_memcpy(reply->key_length, key->key_length, 2);
	os_memcpy(reply->replay_counter, key->replay_counter,
		  WPA_REPLAY_COUNTER_LEN);

	key_mic = (u8 *) (reply + 1);
	WPA_PUT_BE16(key_mic + mic_len, kde_len); /* Key Data Length */

#ifdef CONFIG_OCV
	if (wpa_sm_ocv_enabled(sm)) {
		struct wpa_channel_info ci;
		u8 *pos;

		if (wpa_sm_channel_info(sm, &ci) != 0) {
			wpa_printf(MSG_WARNING,
				   "Failed to get channel info for OCI element in EAPOL-Key 2/2");
			os_free(rbuf);
			return -1;
		}

		pos = key_mic + mic_len + 2; /* Key Data */
		if (ocv_insert_oci_kde(&ci, &pos) < 0) {
			os_free(rbuf);
			return -1;
		}
	}
#endif /* CONFIG_OCV */

	wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG, "WPA: Sending EAPOL-Key 2/2");
	return wpa_eapol_key_send(sm, &sm->ptk, ver, sm->bssid, ETH_P_EAPOL,
				  rbuf, rlen, key_mic);
}