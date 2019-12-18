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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  timeoutie ;
struct wpa_tdls_timeoutie {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kck; } ;
struct wpa_tdls_peer {int /*<<< orphan*/  initiator; scalar_t__ wmm_capable; scalar_t__ ht_capabilities; scalar_t__ vht_capabilities; int /*<<< orphan*/  rsnie_p; TYPE_1__ tpk; int /*<<< orphan*/  lifetime; int /*<<< orphan*/  inonce; int /*<<< orphan*/  rnonce; int /*<<< orphan*/  rsnie_p_len; scalar_t__ rsnie_i_len; } ;
struct wpa_tdls_lnkid {int dummy; } ;
struct wpa_tdls_ftie {int ie_len; int* mic; int /*<<< orphan*/  Snonce; int /*<<< orphan*/  Anonce; int /*<<< orphan*/  ie_type; } ;
struct wpa_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TDLS_PEER_HT ; 
 int /*<<< orphan*/  TDLS_PEER_VHT ; 
 int /*<<< orphan*/  TDLS_PEER_WMM ; 
 int TDLS_TESTING_LONG_FRAME ; 
 int TDLS_TESTING_WRONG_LIFETIME_CONF ; 
 int TDLS_TESTING_WRONG_MIC ; 
 int /*<<< orphan*/  WLAN_EID_FAST_BSS_TRANSITION ; 
 int /*<<< orphan*/  WLAN_TDLS_SETUP_CONFIRM ; 
 int /*<<< orphan*/  WPA_NONCE_LEN ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_zalloc (size_t) ; 
 int tdls_testing ; 
 int /*<<< orphan*/ * wpa_add_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpa_add_tdls_timeoutie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_tdls_ftie_mic (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ wpa_tdls_get_privacy (struct wpa_sm*) ; 
 int wpa_tdls_tpk_send (struct wpa_sm*,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wpa_tdls_send_tpk_m3(struct wpa_sm *sm,
				const unsigned char *src_addr, u8 dtoken,
				struct wpa_tdls_lnkid *lnkid,
				const struct wpa_tdls_peer *peer)
{
	u8 *rbuf, *pos;
	size_t buf_len;
	struct wpa_tdls_ftie *ftie;
	struct wpa_tdls_timeoutie timeoutie;
	u32 lifetime;
	int status;
	u32 peer_capab = 0;

	buf_len = 0;
	if (wpa_tdls_get_privacy(sm)) {
		/* Peer RSN IE, FTIE(Initiator Nonce, Responder Nonce),
		 * Lifetime */
		buf_len += peer->rsnie_i_len + sizeof(struct wpa_tdls_ftie) +
			sizeof(struct wpa_tdls_timeoutie);
#ifdef CONFIG_TDLS_TESTING
		if (tdls_testing & TDLS_TESTING_LONG_FRAME)
			buf_len += 170;
#endif /* CONFIG_TDLS_TESTING */
	}

	rbuf = os_zalloc(buf_len + 1);
	if (rbuf == NULL)
		return -1;
	pos = rbuf;

	if (!wpa_tdls_get_privacy(sm))
		goto skip_ies;

	/* Peer RSN IE */
	pos = wpa_add_ie(pos, peer->rsnie_p, peer->rsnie_p_len);

	ftie = (struct wpa_tdls_ftie *) pos;
	ftie->ie_type = WLAN_EID_FAST_BSS_TRANSITION;
	/*TODO: ftie->mic_control to set 3-CONFIRM */
	os_memcpy(ftie->Anonce, peer->rnonce, WPA_NONCE_LEN);
	os_memcpy(ftie->Snonce, peer->inonce, WPA_NONCE_LEN);
	ftie->ie_len = sizeof(struct wpa_tdls_ftie) - 2;

	pos = (u8 *) (ftie + 1);

#ifdef CONFIG_TDLS_TESTING
	if (tdls_testing & TDLS_TESTING_LONG_FRAME) {
		wpa_printf(MSG_DEBUG, "TDLS: Testing - add extra subelem to "
			   "FTIE");
		ftie->ie_len += 170;
		*pos++ = 255; /* FTIE subelem */
		*pos++ = 168; /* FTIE subelem length */
		pos += 168;
	}
#endif /* CONFIG_TDLS_TESTING */

	/* Lifetime */
	lifetime = peer->lifetime;
#ifdef CONFIG_TDLS_TESTING
	if (tdls_testing & TDLS_TESTING_WRONG_LIFETIME_CONF) {
		wpa_printf(MSG_DEBUG, "TDLS: Testing - use wrong TPK "
			   "lifetime in confirm");
		lifetime++;
	}
#endif /* CONFIG_TDLS_TESTING */
	pos = wpa_add_tdls_timeoutie(pos, (u8 *) &timeoutie,
				     sizeof(timeoutie), lifetime);
	wpa_printf(MSG_DEBUG, "TDLS: TPK lifetime %u seconds",
		   lifetime);

	/* compute MIC before sending */
	wpa_tdls_ftie_mic(peer->tpk.kck, 3, (u8 *) lnkid, peer->rsnie_p,
			  (u8 *) &timeoutie, (u8 *) ftie, ftie->mic);
#ifdef CONFIG_TDLS_TESTING
	if (tdls_testing & TDLS_TESTING_WRONG_MIC) {
		wpa_printf(MSG_DEBUG, "TDLS: Testing - use wrong MIC");
		ftie->mic[0] ^= 0x01;
	}
#endif /* CONFIG_TDLS_TESTING */

skip_ies:

	if (peer->vht_capabilities)
		peer_capab |= TDLS_PEER_VHT;
	if (peer->ht_capabilities)
		peer_capab |= TDLS_PEER_HT;
	if (peer->wmm_capable)
		peer_capab |= TDLS_PEER_WMM;

	status = wpa_tdls_tpk_send(sm, src_addr, WLAN_TDLS_SETUP_CONFIRM,
				   dtoken, 0, peer_capab, peer->initiator,
				   rbuf, pos - rbuf);
	os_free(rbuf);

	return status;
}