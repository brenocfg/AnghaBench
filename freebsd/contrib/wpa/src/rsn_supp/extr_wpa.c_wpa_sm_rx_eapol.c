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
struct wpa_sm {scalar_t__ pairwise_cipher; scalar_t__ group_cipher; scalar_t__ proto; TYPE_1__* ctx; int /*<<< orphan*/  rx_replay_counter; scalar_t__ rx_replay_counter_set; int /*<<< orphan*/  key_mgmt; int /*<<< orphan*/  eapol; int /*<<< orphan*/  pmk_len; scalar_t__ ft_completed; } ;
struct wpa_eapol_key {unsigned long type; int /*<<< orphan*/  replay_counter; int /*<<< orphan*/ * key_info; } ;
struct ieee802_1x_hdr {unsigned long type; int /*<<< orphan*/  version; int /*<<< orphan*/  length; } ;
struct TYPE_2__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 unsigned long EAPOL_KEY_TYPE_RSN ; 
 unsigned long EAPOL_KEY_TYPE_WPA ; 
 int /*<<< orphan*/  EAPOL_VERSION ; 
 unsigned long IEEE802_1X_TYPE_EAPOL_KEY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ WPA_CIPHER_CCMP ; 
 scalar_t__ WPA_CIPHER_GCMP ; 
 void* WPA_GET_BE16 (int /*<<< orphan*/ *) ; 
 int WPA_KEY_INFO_ACK ; 
 int WPA_KEY_INFO_ENCR_KEY_DATA ; 
 int WPA_KEY_INFO_KEY_INDEX_MASK ; 
 int WPA_KEY_INFO_KEY_TYPE ; 
 int WPA_KEY_INFO_MIC ; 
 int WPA_KEY_INFO_REQUEST ; 
 int WPA_KEY_INFO_SMK_MESSAGE ; 
 int WPA_KEY_INFO_TYPE_AES_128_CMAC ; 
 int WPA_KEY_INFO_TYPE_AKM_DEFINED ; 
 int WPA_KEY_INFO_TYPE_HMAC_MD5_RC4 ; 
 int WPA_KEY_INFO_TYPE_HMAC_SHA1_AES ; 
 int WPA_KEY_INFO_TYPE_MASK ; 
 scalar_t__ WPA_PROTO_OSEN ; 
 scalar_t__ WPA_PROTO_RSN ; 
 int /*<<< orphan*/  WPA_REPLAY_COUNTER_LEN ; 
 size_t be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  eapol_sm_notify_lower_layer_success (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 int /*<<< orphan*/  wpa_eapol_key_dump (struct wpa_sm*,struct wpa_eapol_key*,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ wpa_key_mgmt_ft (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_sha256 (int /*<<< orphan*/ ) ; 
 size_t wpa_mic_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_supp_aead_decrypt (struct wpa_sm*,int /*<<< orphan*/ *,size_t,size_t*) ; 
 scalar_t__ wpa_supplicant_decrypt_key_data (struct wpa_sm*,struct wpa_eapol_key*,size_t,int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  wpa_supplicant_process_1_of_2 (struct wpa_sm*,int /*<<< orphan*/  const*,struct wpa_eapol_key*,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  wpa_supplicant_process_1_of_4 (struct wpa_sm*,int /*<<< orphan*/  const*,struct wpa_eapol_key*,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_supplicant_process_3_of_4 (struct wpa_sm*,struct wpa_eapol_key*,int,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ wpa_supplicant_verify_eapol_key_mic (struct wpa_sm*,struct wpa_eapol_key*,int,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ wpa_use_akm_defined (int /*<<< orphan*/ ) ; 

int wpa_sm_rx_eapol(struct wpa_sm *sm, const u8 *src_addr,
		    const u8 *buf, size_t len)
{
	size_t plen, data_len, key_data_len;
	const struct ieee802_1x_hdr *hdr;
	struct wpa_eapol_key *key;
	u16 key_info, ver;
	u8 *tmp = NULL;
	int ret = -1;
	u8 *mic, *key_data;
	size_t mic_len, keyhdrlen;

#ifdef CONFIG_IEEE80211R
	sm->ft_completed = 0;
#endif /* CONFIG_IEEE80211R */

	mic_len = wpa_mic_len(sm->key_mgmt, sm->pmk_len);
	keyhdrlen = sizeof(*key) + mic_len + 2;

	if (len < sizeof(*hdr) + keyhdrlen) {
		wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
			"WPA: EAPOL frame too short to be a WPA "
			"EAPOL-Key (len %lu, expecting at least %lu)",
			(unsigned long) len,
			(unsigned long) sizeof(*hdr) + keyhdrlen);
		return 0;
	}

	hdr = (const struct ieee802_1x_hdr *) buf;
	plen = be_to_host16(hdr->length);
	data_len = plen + sizeof(*hdr);
	wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
		"IEEE 802.1X RX: version=%d type=%d length=%lu",
		hdr->version, hdr->type, (unsigned long) plen);

	if (hdr->version < EAPOL_VERSION) {
		/* TODO: backwards compatibility */
	}
	if (hdr->type != IEEE802_1X_TYPE_EAPOL_KEY) {
		wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
			"WPA: EAPOL frame (type %u) discarded, "
			"not a Key frame", hdr->type);
		ret = 0;
		goto out;
	}
	wpa_hexdump(MSG_MSGDUMP, "WPA: RX EAPOL-Key", buf, len);
	if (plen > len - sizeof(*hdr) || plen < keyhdrlen) {
		wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
			"WPA: EAPOL frame payload size %lu "
			"invalid (frame size %lu)",
			(unsigned long) plen, (unsigned long) len);
		ret = 0;
		goto out;
	}
	if (data_len < len) {
		wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
			"WPA: ignoring %lu bytes after the IEEE 802.1X data",
			(unsigned long) len - data_len);
	}

	/*
	 * Make a copy of the frame since we need to modify the buffer during
	 * MAC validation and Key Data decryption.
	 */
	tmp = os_memdup(buf, data_len);
	if (tmp == NULL)
		goto out;
	key = (struct wpa_eapol_key *) (tmp + sizeof(struct ieee802_1x_hdr));
	mic = (u8 *) (key + 1);
	key_data = mic + mic_len + 2;

	if (key->type != EAPOL_KEY_TYPE_WPA && key->type != EAPOL_KEY_TYPE_RSN)
	{
		wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
			"WPA: EAPOL-Key type (%d) unknown, discarded",
			key->type);
		ret = 0;
		goto out;
	}

	key_data_len = WPA_GET_BE16(mic + mic_len);
	wpa_eapol_key_dump(sm, key, key_data_len, mic, mic_len);

	if (key_data_len > plen - keyhdrlen) {
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO, "WPA: Invalid EAPOL-Key "
			"frame - key_data overflow (%u > %u)",
			(unsigned int) key_data_len,
			(unsigned int) (plen - keyhdrlen));
		goto out;
	}

	eapol_sm_notify_lower_layer_success(sm->eapol, 0);
	key_info = WPA_GET_BE16(key->key_info);
	ver = key_info & WPA_KEY_INFO_TYPE_MASK;
	if (ver != WPA_KEY_INFO_TYPE_HMAC_MD5_RC4 &&
#if defined(CONFIG_IEEE80211R) || defined(CONFIG_IEEE80211W)
	    ver != WPA_KEY_INFO_TYPE_AES_128_CMAC &&
#endif /* CONFIG_IEEE80211R || CONFIG_IEEE80211W */
	    ver != WPA_KEY_INFO_TYPE_HMAC_SHA1_AES &&
	    !wpa_use_akm_defined(sm->key_mgmt)) {
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
			"WPA: Unsupported EAPOL-Key descriptor version %d",
			ver);
		goto out;
	}

	if (wpa_use_akm_defined(sm->key_mgmt) &&
	    ver != WPA_KEY_INFO_TYPE_AKM_DEFINED) {
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
			"RSN: Unsupported EAPOL-Key descriptor version %d (expected AKM defined = 0)",
			ver);
		goto out;
	}

#ifdef CONFIG_IEEE80211R
	if (wpa_key_mgmt_ft(sm->key_mgmt)) {
		/* IEEE 802.11r uses a new key_info type (AES-128-CMAC). */
		if (ver != WPA_KEY_INFO_TYPE_AES_128_CMAC &&
		    !wpa_use_akm_defined(sm->key_mgmt)) {
			wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
				"FT: AP did not use AES-128-CMAC");
			goto out;
		}
	} else
#endif /* CONFIG_IEEE80211R */
#ifdef CONFIG_IEEE80211W
	if (wpa_key_mgmt_sha256(sm->key_mgmt)) {
		if (ver != WPA_KEY_INFO_TYPE_AES_128_CMAC &&
		    !wpa_use_akm_defined(sm->key_mgmt)) {
			wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
				"WPA: AP did not use the "
				"negotiated AES-128-CMAC");
			goto out;
		}
	} else
#endif /* CONFIG_IEEE80211W */
	if (sm->pairwise_cipher == WPA_CIPHER_CCMP &&
	    !wpa_use_akm_defined(sm->key_mgmt) &&
	    ver != WPA_KEY_INFO_TYPE_HMAC_SHA1_AES) {
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
			"WPA: CCMP is used, but EAPOL-Key "
			"descriptor version (%d) is not 2", ver);
		if (sm->group_cipher != WPA_CIPHER_CCMP &&
		    !(key_info & WPA_KEY_INFO_KEY_TYPE)) {
			/* Earlier versions of IEEE 802.11i did not explicitly
			 * require version 2 descriptor for all EAPOL-Key
			 * packets, so allow group keys to use version 1 if
			 * CCMP is not used for them. */
			wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
				"WPA: Backwards compatibility: allow invalid "
				"version for non-CCMP group keys");
		} else if (ver == WPA_KEY_INFO_TYPE_AES_128_CMAC) {
			wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
				"WPA: Interoperability workaround: allow incorrect (should have been HMAC-SHA1), but stronger (is AES-128-CMAC), descriptor version to be used");
		} else
			goto out;
	} else if (sm->pairwise_cipher == WPA_CIPHER_GCMP &&
		   !wpa_use_akm_defined(sm->key_mgmt) &&
		   ver != WPA_KEY_INFO_TYPE_HMAC_SHA1_AES) {
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
			"WPA: GCMP is used, but EAPOL-Key "
			"descriptor version (%d) is not 2", ver);
		goto out;
	}

	if (sm->rx_replay_counter_set &&
	    os_memcmp(key->replay_counter, sm->rx_replay_counter,
		      WPA_REPLAY_COUNTER_LEN) <= 0) {
		wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
			"WPA: EAPOL-Key Replay Counter did not increase - "
			"dropping packet");
		goto out;
	}

	if (key_info & WPA_KEY_INFO_SMK_MESSAGE) {
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
			"WPA: Unsupported SMK bit in key_info");
		goto out;
	}

	if (!(key_info & WPA_KEY_INFO_ACK)) {
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
			"WPA: No Ack bit in key_info");
		goto out;
	}

	if (key_info & WPA_KEY_INFO_REQUEST) {
		wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
			"WPA: EAPOL-Key with Request bit - dropped");
		goto out;
	}

	if ((key_info & WPA_KEY_INFO_MIC) &&
	    wpa_supplicant_verify_eapol_key_mic(sm, key, ver, tmp, data_len))
		goto out;

#ifdef CONFIG_FILS
	if (!mic_len && (key_info & WPA_KEY_INFO_ENCR_KEY_DATA)) {
		if (wpa_supp_aead_decrypt(sm, tmp, data_len, &key_data_len))
			goto out;
	}
#endif /* CONFIG_FILS */

	if ((sm->proto == WPA_PROTO_RSN || sm->proto == WPA_PROTO_OSEN) &&
	    (key_info & WPA_KEY_INFO_ENCR_KEY_DATA) && mic_len) {
		/*
		 * Only decrypt the Key Data field if the frame's authenticity
		 * was verified. When using AES-SIV (FILS), the MIC flag is not
		 * set, so this check should only be performed if mic_len != 0
		 * which is the case in this code branch.
		 */
		if (!(key_info & WPA_KEY_INFO_MIC)) {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"WPA: Ignore EAPOL-Key with encrypted but unauthenticated data");
			goto out;
		}
		if (wpa_supplicant_decrypt_key_data(sm, key, mic_len,
						    ver, key_data,
						    &key_data_len))
			goto out;
	}

	if (key_info & WPA_KEY_INFO_KEY_TYPE) {
		if (key_info & WPA_KEY_INFO_KEY_INDEX_MASK) {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"WPA: Ignored EAPOL-Key (Pairwise) with "
				"non-zero key index");
			goto out;
		}
		if (key_info & (WPA_KEY_INFO_MIC |
				WPA_KEY_INFO_ENCR_KEY_DATA)) {
			/* 3/4 4-Way Handshake */
			wpa_supplicant_process_3_of_4(sm, key, ver, key_data,
						      key_data_len);
		} else {
			/* 1/4 4-Way Handshake */
			wpa_supplicant_process_1_of_4(sm, src_addr, key,
						      ver, key_data,
						      key_data_len);
		}
	} else {
		if ((mic_len && (key_info & WPA_KEY_INFO_MIC)) ||
		    (!mic_len && (key_info & WPA_KEY_INFO_ENCR_KEY_DATA))) {
			/* 1/2 Group Key Handshake */
			wpa_supplicant_process_1_of_2(sm, src_addr, key,
						      key_data, key_data_len,
						      ver);
		} else {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"WPA: EAPOL-Key (Group) without Mic/Encr bit - "
				"dropped");
		}
	}

	ret = 1;

out:
	bin_clear_free(tmp, data_len);
	return ret;
}