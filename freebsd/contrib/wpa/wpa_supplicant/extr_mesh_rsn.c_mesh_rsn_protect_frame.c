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
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
struct sta_info {scalar_t__ const* addr; int /*<<< orphan*/  aek; int /*<<< orphan*/  peer_nonce; int /*<<< orphan*/  my_nonce; } ;
struct mesh_rsn {scalar_t__ igtk_len; int /*<<< orphan*/  igtk; int /*<<< orphan*/  igtk_key_id; TYPE_1__* wpa_s; int /*<<< orphan*/  mgtk_key_id; scalar_t__ mgtk_len; int /*<<< orphan*/  mgtk; } ;
struct ieee80211_ampe_ie {scalar_t__* local_nonce; scalar_t__* peer_nonce; int /*<<< orphan*/  selected_pairwise_suite; } ;
struct TYPE_2__ {scalar_t__ const* own_addr; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ const PLINK_OPEN ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_CCMP ; 
 int /*<<< orphan*/  RSN_SELECTOR_PUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WLAN_EID_AMPE ; 
 scalar_t__ WLAN_EID_MIC ; 
 scalar_t__ WPA_KEY_RSC_LEN ; 
 scalar_t__ WPA_NONCE_LEN ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_PUT_LE32 (scalar_t__*,int) ; 
 scalar_t__ aes_siv_encrypt (int /*<<< orphan*/ ,int,scalar_t__*,int,int,scalar_t__ const**,size_t const*,scalar_t__*) ; 
 int /*<<< orphan*/  os_free (scalar_t__*) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_drv_get_seqnum (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__* wpabuf_head_u8 (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 
 scalar_t__* wpabuf_put (struct wpabuf*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,scalar_t__) ; 
 scalar_t__ wpabuf_tailroom (struct wpabuf*) ; 

int mesh_rsn_protect_frame(struct mesh_rsn *rsn, struct sta_info *sta,
			   const u8 *cat, struct wpabuf *buf)
{
	struct ieee80211_ampe_ie *ampe;
	u8 const *ie = wpabuf_head_u8(buf) + wpabuf_len(buf);
	u8 *ampe_ie, *pos, *mic_payload;
	const u8 *aad[] = { rsn->wpa_s->own_addr, sta->addr, cat };
	const size_t aad_len[] = { ETH_ALEN, ETH_ALEN, ie - cat };
	int ret = 0;
	size_t len;

	len = sizeof(*ampe);
	if (cat[1] == PLINK_OPEN)
		len += rsn->mgtk_len + WPA_KEY_RSC_LEN + 4;
#ifdef CONFIG_IEEE80211W
	if (cat[1] == PLINK_OPEN && rsn->igtk_len)
		len += 2 + 6 + rsn->igtk_len;
#endif /* CONFIG_IEEE80211W */

	if (2 + AES_BLOCK_SIZE + 2 + len > wpabuf_tailroom(buf)) {
		wpa_printf(MSG_ERROR, "protect frame: buffer too small");
		return -EINVAL;
	}

	ampe_ie = os_zalloc(2 + len);
	if (!ampe_ie) {
		wpa_printf(MSG_ERROR, "protect frame: out of memory");
		return -ENOMEM;
	}

	/*  IE: AMPE */
	ampe_ie[0] = WLAN_EID_AMPE;
	ampe_ie[1] = len;
	ampe = (struct ieee80211_ampe_ie *) (ampe_ie + 2);

	RSN_SELECTOR_PUT(ampe->selected_pairwise_suite,
			 RSN_CIPHER_SUITE_CCMP);
	os_memcpy(ampe->local_nonce, sta->my_nonce, WPA_NONCE_LEN);
	os_memcpy(ampe->peer_nonce, sta->peer_nonce, WPA_NONCE_LEN);

	pos = (u8 *) (ampe + 1);
	if (cat[1] != PLINK_OPEN)
		goto skip_keys;

	/* TODO: Key Replay Counter[8] optionally for
	 * Mesh Group Key Inform/Acknowledge frames */

	/* TODO: static mgtk for now since we don't support rekeying! */
	/*
	 * GTKdata[variable]:
	 * MGTK[variable] || Key RSC[8] || GTKExpirationTime[4]
	 */
	os_memcpy(pos, rsn->mgtk, rsn->mgtk_len);
	pos += rsn->mgtk_len;
	wpa_drv_get_seqnum(rsn->wpa_s, NULL, rsn->mgtk_key_id, pos);
	pos += WPA_KEY_RSC_LEN;
	/* Use fixed GTKExpirationTime for now */
	WPA_PUT_LE32(pos, 0xffffffff);
	pos += 4;

#ifdef CONFIG_IEEE80211W
	/*
	 * IGTKdata[variable]:
	 * Key ID[2], IPN[6], IGTK[variable]
	 */
	if (rsn->igtk_len) {
		WPA_PUT_LE16(pos, rsn->igtk_key_id);
		pos += 2;
		wpa_drv_get_seqnum(rsn->wpa_s, NULL, rsn->igtk_key_id, pos);
		pos += 6;
		os_memcpy(pos, rsn->igtk, rsn->igtk_len);
	}
#endif /* CONFIG_IEEE80211W */

skip_keys:
	wpa_hexdump_key(MSG_DEBUG, "mesh: Plaintext AMPE element",
			ampe_ie, 2 + len);

	/* IE: MIC */
	wpabuf_put_u8(buf, WLAN_EID_MIC);
	wpabuf_put_u8(buf, AES_BLOCK_SIZE);
	/* MIC field is output ciphertext */

	/* encrypt after MIC */
	mic_payload = wpabuf_put(buf, 2 + len + AES_BLOCK_SIZE);

	if (aes_siv_encrypt(sta->aek, sizeof(sta->aek), ampe_ie, 2 + len, 3,
			    aad, aad_len, mic_payload)) {
		wpa_printf(MSG_ERROR, "protect frame: failed to encrypt");
		ret = -ENOMEM;
	}

	os_free(ampe_ie);

	return ret;
}