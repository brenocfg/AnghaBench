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
typedef  size_t uint16_t ;
struct ieee80211vap {scalar_t__ iv_opmode; struct ieee80211_key* iv_nw_keys; TYPE_1__* iv_ic; int /*<<< orphan*/  iv_bss; } ;
struct ieee80211req_key {int ik_keylen; size_t ik_keyix; int ik_flags; int /*<<< orphan*/  ik_macaddr; int /*<<< orphan*/  ik_keydata; int /*<<< orphan*/  ik_keyrsc; int /*<<< orphan*/  ik_type; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct ieee80211_key {size_t wk_keyix; int wk_keylen; int /*<<< orphan*/  wk_macaddr; int /*<<< orphan*/  wk_key; scalar_t__ wk_keytsc; int /*<<< orphan*/ * wk_keyrsc; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_macaddr; struct ieee80211_key ni_ucastkey; int /*<<< orphan*/  ni_bssid; } ;
typedef  int /*<<< orphan*/  ik ;
struct TYPE_2__ {int /*<<< orphan*/  ic_sta; } ;

/* Variables and functions */
 int E2BIG ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ADDR_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_KEYBUF_SIZE ; 
 size_t IEEE80211_KEYIX_NONE ; 
 int IEEE80211_KEY_DEFAULT ; 
 int IEEE80211_KEY_RECV ; 
 int IEEE80211_KEY_XMIT ; 
 scalar_t__ IEEE80211_M_STA ; 
 int IEEE80211_TID_SIZE ; 
 size_t IEEE80211_WEP_NKID ; 
 int copyin (int /*<<< orphan*/ ,struct ieee80211req_key*,int) ; 
 scalar_t__ ieee80211_crypto_newkey (struct ieee80211vap*,int /*<<< orphan*/ ,int,struct ieee80211_key*) ; 
 int /*<<< orphan*/  ieee80211_crypto_set_deftxkey (struct ieee80211vap*,size_t) ; 
 int /*<<< orphan*/  ieee80211_crypto_setkey (struct ieee80211vap*,struct ieee80211_key*) ; 
 struct ieee80211_node* ieee80211_find_vap_node (int /*<<< orphan*/ *,struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_key_update_begin (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_key_update_end (struct ieee80211vap*) ; 
 struct ieee80211_node* ieee80211_ref_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ieee80211_ioctl_setkey(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211req_key ik;
	struct ieee80211_node *ni;
	struct ieee80211_key *wk;
	uint16_t kid;
	int error, i;

	if (ireq->i_len != sizeof(ik))
		return EINVAL;
	error = copyin(ireq->i_data, &ik, sizeof(ik));
	if (error)
		return error;
	/* NB: cipher support is verified by ieee80211_crypt_newkey */
	/* NB: this also checks ik->ik_keylen > sizeof(wk->wk_key) */
	if (ik.ik_keylen > sizeof(ik.ik_keydata))
		return E2BIG;
	kid = ik.ik_keyix;
	if (kid == IEEE80211_KEYIX_NONE) {
		/* XXX unicast keys currently must be tx/rx */
		if (ik.ik_flags != (IEEE80211_KEY_XMIT | IEEE80211_KEY_RECV))
			return EINVAL;
		if (vap->iv_opmode == IEEE80211_M_STA) {
			ni = ieee80211_ref_node(vap->iv_bss);
			if (!IEEE80211_ADDR_EQ(ik.ik_macaddr, ni->ni_bssid)) {
				ieee80211_free_node(ni);
				return EADDRNOTAVAIL;
			}
		} else {
			ni = ieee80211_find_vap_node(&vap->iv_ic->ic_sta, vap,
				ik.ik_macaddr);
			if (ni == NULL)
				return ENOENT;
		}
		wk = &ni->ni_ucastkey;
	} else {
		if (kid >= IEEE80211_WEP_NKID)
			return EINVAL;
		wk = &vap->iv_nw_keys[kid];
		/*
		 * Global slots start off w/o any assigned key index.
		 * Force one here for consistency with IEEE80211_IOC_WEPKEY.
		 */
		if (wk->wk_keyix == IEEE80211_KEYIX_NONE)
			wk->wk_keyix = kid;
		ni = NULL;
	}
	error = 0;
	ieee80211_key_update_begin(vap);
	if (ieee80211_crypto_newkey(vap, ik.ik_type, ik.ik_flags, wk)) {
		wk->wk_keylen = ik.ik_keylen;
		/* NB: MIC presence is implied by cipher type */
		if (wk->wk_keylen > IEEE80211_KEYBUF_SIZE)
			wk->wk_keylen = IEEE80211_KEYBUF_SIZE;
		for (i = 0; i < IEEE80211_TID_SIZE; i++)
			wk->wk_keyrsc[i] = ik.ik_keyrsc;
		wk->wk_keytsc = 0;			/* new key, reset */
		memset(wk->wk_key, 0, sizeof(wk->wk_key));
		memcpy(wk->wk_key, ik.ik_keydata, ik.ik_keylen);
		IEEE80211_ADDR_COPY(wk->wk_macaddr,
		    ni != NULL ?  ni->ni_macaddr : ik.ik_macaddr);
		if (!ieee80211_crypto_setkey(vap, wk))
			error = EIO;
		else if ((ik.ik_flags & IEEE80211_KEY_DEFAULT))
			/*
			 * Inform the driver that this is the default
			 * transmit key.  Now, ideally we'd just set
			 * a flag in the key update that would
			 * say "yes, we're the default key", but
			 * that currently isn't the way the ioctl ->
			 * key interface works.
			 */
			ieee80211_crypto_set_deftxkey(vap, kid);
	} else
		error = ENXIO;
	ieee80211_key_update_end(vap);
	if (ni != NULL)
		ieee80211_free_node(ni);
	return error;
}