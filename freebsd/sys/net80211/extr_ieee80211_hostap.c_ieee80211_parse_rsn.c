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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct ieee80211vap {int iv_flags; } ;
struct ieee80211_rsnparms {int rsn_mcastcipher; int rsn_ucastcipher; int rsn_keymgmt; void* rsn_caps; int /*<<< orphan*/  rsn_ucastkeylen; int /*<<< orphan*/  rsn_mcastkeylen; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int IEEE80211_CIPHER_AES_CCM ; 
 int IEEE80211_CIPHER_AES_OCB ; 
 int IEEE80211_CIPHER_NONE ; 
 int IEEE80211_CIPHER_TKIP ; 
 int IEEE80211_CIPHER_WEP ; 
 int /*<<< orphan*/  IEEE80211_DISCARD_IE (struct ieee80211vap*,int,struct ieee80211_frame const*,char*,char*,int,...) ; 
 int IEEE80211_F_WPA2 ; 
 int IEEE80211_MSG_ELEMID ; 
 int IEEE80211_MSG_WPA ; 
 int IEEE80211_REASON_GROUP_CIPHER_INVALID ; 
 int IEEE80211_REASON_IE_INVALID ; 
 int IEEE80211_REASON_PAIRWISE_CIPHER_INVALID ; 
 int IEEE80211_REASON_UNSUPP_RSN_IE_VERSION ; 
 int RSN_ASE_8021X_PSK ; 
 int RSN_ASE_8021X_UNSPEC ; 
 int RSN_VERSION ; 
 void* le16dec (int const*) ; 
 int /*<<< orphan*/  le32dec (int const*) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rsnparms*,int /*<<< orphan*/ ,int) ; 
 int rsn_cipher (int const*,int /*<<< orphan*/ *,int*) ; 
 int rsn_keymgmt (int const*) ; 

__attribute__((used)) static int
ieee80211_parse_rsn(struct ieee80211vap *vap, const uint8_t *frm,
	struct ieee80211_rsnparms *rsn, const struct ieee80211_frame *wh)
{
	uint8_t len = frm[1];
	uint32_t w;
	int error, n;

	/*
	 * Check the length once for fixed parts: 
	 * version, mcast cipher, and 2 selector counts.
	 * Other, variable-length data, must be checked separately.
	 */
	if ((vap->iv_flags & IEEE80211_F_WPA2) == 0) {
		IEEE80211_DISCARD_IE(vap,
		    IEEE80211_MSG_ELEMID | IEEE80211_MSG_WPA,
		    wh, "WPA", "not RSN, flags 0x%x", vap->iv_flags);
		return IEEE80211_REASON_IE_INVALID;
	}
	/* XXX may be shorter */
	if (len < 10) {
		IEEE80211_DISCARD_IE(vap,
		    IEEE80211_MSG_ELEMID | IEEE80211_MSG_WPA,
		    wh, "RSN", "too short, len %u", len);
		return IEEE80211_REASON_IE_INVALID;
	}
	frm += 2;
	w = le16dec(frm);
	if (w != RSN_VERSION) {
		IEEE80211_DISCARD_IE(vap,
		    IEEE80211_MSG_ELEMID | IEEE80211_MSG_WPA,
		    wh, "RSN", "bad version %u", w);
		return IEEE80211_REASON_UNSUPP_RSN_IE_VERSION;
	}
	frm += 2, len -= 2;

	memset(rsn, 0, sizeof(*rsn));

	/* multicast/group cipher */
	error = rsn_cipher(frm, &rsn->rsn_mcastkeylen, &rsn->rsn_mcastcipher);
	if (error != 0) {
		IEEE80211_DISCARD_IE(vap,
		    IEEE80211_MSG_ELEMID | IEEE80211_MSG_WPA,
		    wh, "RSN", "unknown mcast cipher suite %08X",
		    le32dec(frm));
		return IEEE80211_REASON_GROUP_CIPHER_INVALID;
	}
	if (rsn->rsn_mcastcipher == IEEE80211_CIPHER_NONE) {
		IEEE80211_DISCARD_IE(vap,
		    IEEE80211_MSG_ELEMID | IEEE80211_MSG_WPA,
		    wh, "RSN", "invalid mcast cipher suite %d",
		    rsn->rsn_mcastcipher);
		return IEEE80211_REASON_GROUP_CIPHER_INVALID;
	}
	frm += 4, len -= 4;

	/* unicast ciphers */
	n = le16dec(frm);
	frm += 2, len -= 2;
	if (len < n*4+2) {
		IEEE80211_DISCARD_IE(vap,
		    IEEE80211_MSG_ELEMID | IEEE80211_MSG_WPA,
		    wh, "RSN", "ucast cipher data too short; len %u, n %u",
		    len, n);
		return IEEE80211_REASON_IE_INVALID;
	}
	w = 0;

	for (; n > 0; n--) {
		uint8_t cipher;

		error = rsn_cipher(frm, &rsn->rsn_ucastkeylen, &cipher);
		if (error == 0)
			w |= 1 << cipher;

		frm += 4, len -= 4;
	}
        if (w & (1 << IEEE80211_CIPHER_AES_CCM))
                rsn->rsn_ucastcipher = IEEE80211_CIPHER_AES_CCM;
	else if (w & (1 << IEEE80211_CIPHER_AES_OCB))
		rsn->rsn_ucastcipher = IEEE80211_CIPHER_AES_OCB;
	else if (w & (1 << IEEE80211_CIPHER_TKIP))
		rsn->rsn_ucastcipher = IEEE80211_CIPHER_TKIP;
	else if ((w & (1 << IEEE80211_CIPHER_NONE)) &&
	    (rsn->rsn_mcastcipher == IEEE80211_CIPHER_WEP ||
	     rsn->rsn_mcastcipher == IEEE80211_CIPHER_TKIP))
		rsn->rsn_ucastcipher = IEEE80211_CIPHER_NONE;
	else {
		IEEE80211_DISCARD_IE(vap,
		    IEEE80211_MSG_ELEMID | IEEE80211_MSG_WPA,
		    wh, "RSN", "no usable pairwise cipher suite found (w=%d)",
		    w);
		return IEEE80211_REASON_PAIRWISE_CIPHER_INVALID;
	}

	/* key management algorithms */
	n = le16dec(frm);
	frm += 2, len -= 2;
	if (len < n*4) {
		IEEE80211_DISCARD_IE(vap,
		    IEEE80211_MSG_ELEMID | IEEE80211_MSG_WPA,
		    wh, "RSN", "key mgmt alg data too short; len %u, n %u",
		    len, n);
		return IEEE80211_REASON_IE_INVALID;
	}
	w = 0;
	for (; n > 0; n--) {
		w |= rsn_keymgmt(frm);
		frm += 4, len -= 4;
	}
	if (w & RSN_ASE_8021X_UNSPEC)
		rsn->rsn_keymgmt = RSN_ASE_8021X_UNSPEC;
	else
		rsn->rsn_keymgmt = RSN_ASE_8021X_PSK;

	/* optional RSN capabilities */
	if (len > 2)
		rsn->rsn_caps = le16dec(frm);
	/* XXXPMKID */

	return 0;
}