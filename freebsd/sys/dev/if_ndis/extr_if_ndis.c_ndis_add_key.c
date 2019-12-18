#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ndis_softc {int dummy; } ;
struct ieee80211vap {TYPE_3__* iv_bss; TYPE_1__* iv_ic; } ;
struct ieee80211_key {int wk_keylen; int wk_flags; int wk_keyix; int /*<<< orphan*/  wk_key; int /*<<< orphan*/ * wk_keyrsc; TYPE_2__* wk_cipher; } ;
typedef  int /*<<< orphan*/  rkey ;
struct TYPE_9__ {int nk_len; int nk_keylen; int nk_keyidx; int /*<<< orphan*/  nk_keydata; int /*<<< orphan*/  nk_keyrsc; int /*<<< orphan*/  nk_bssid; } ;
typedef  TYPE_4__ ndis_80211_key ;
struct TYPE_8__ {int /*<<< orphan*/  ni_bssid; } ;
struct TYPE_7__ {int ic_cipher; } ;
struct TYPE_6__ {struct ndis_softc* ic_softc; } ;

/* Variables and functions */
 int ENOTTY ; 
 int IEEE80211_ADDR_LEN ; 
#define  IEEE80211_CIPHER_AES_CCM 130 
#define  IEEE80211_CIPHER_TKIP 129 
#define  IEEE80211_CIPHER_WEP 128 
 int IEEE80211_KEYIX_NONE ; 
 int IEEE80211_KEY_GROUP ; 
 int IEEE80211_KEY_SWMIC ; 
 int IEEE80211_KEY_XMIT ; 
 int /*<<< orphan*/  OID_802_11_ADD_KEY ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  ieee80211broadcastaddr ; 
 int ndis_set_info (struct ndis_softc*,int /*<<< orphan*/ ,TYPE_4__*,int*) ; 

__attribute__((used)) static int
ndis_add_key(struct ieee80211vap *vap, const struct ieee80211_key *key)
{
	struct ndis_softc	*sc = vap->iv_ic->ic_softc;
	ndis_80211_key		rkey;
	int			len, error = 0;

	switch (key->wk_cipher->ic_cipher) {
	case IEEE80211_CIPHER_TKIP:

		len = sizeof(ndis_80211_key);
		bzero((char *)&rkey, sizeof(rkey));

		rkey.nk_len = len;
		rkey.nk_keylen = key->wk_keylen;

		if (key->wk_flags & IEEE80211_KEY_SWMIC)
			rkey.nk_keylen += 16;

		/* key index - gets weird in NDIS */

		if (key->wk_keyix != IEEE80211_KEYIX_NONE)
			rkey.nk_keyidx = key->wk_keyix;
		else
			rkey.nk_keyidx = 0;

		if (key->wk_flags & IEEE80211_KEY_XMIT)
			rkey.nk_keyidx |= 1 << 31;

		if (key->wk_flags & IEEE80211_KEY_GROUP) {
			bcopy(ieee80211broadcastaddr,
			    rkey.nk_bssid, IEEE80211_ADDR_LEN);
		} else {
			bcopy(vap->iv_bss->ni_bssid,
			    rkey.nk_bssid, IEEE80211_ADDR_LEN);
			/* pairwise key */
			rkey.nk_keyidx |= 1 << 30;
		}

		/* need to set bit 29 based on keyrsc */
		rkey.nk_keyrsc = key->wk_keyrsc[0];	/* XXX need tid */

		if (rkey.nk_keyrsc)
			rkey.nk_keyidx |= 1 << 29;

		if (key->wk_flags & IEEE80211_KEY_SWMIC) {
			bcopy(key->wk_key, rkey.nk_keydata, 16);
			bcopy(key->wk_key + 24, rkey.nk_keydata + 16, 8);
			bcopy(key->wk_key + 16, rkey.nk_keydata + 24, 8);
		} else
			bcopy(key->wk_key, rkey.nk_keydata, key->wk_keylen);

		error = ndis_set_info(sc, OID_802_11_ADD_KEY, &rkey, &len);
		break;
	case IEEE80211_CIPHER_WEP:
		error = 0;
		break;
	/*
	 * I don't know how to set up keys for the AES
	 * cipher yet. Is it the same as TKIP?
	 */
	case IEEE80211_CIPHER_AES_CCM:
	default:
		error = ENOTTY;
		break;
	}

	/* We need to return 1 for success, 0 for failure. */

	if (error)
		return (0);

	return (1);
}