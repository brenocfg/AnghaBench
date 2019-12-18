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
typedef  size_t u_int ;
struct ieee80211vap {scalar_t__ iv_def_txkey; TYPE_1__* iv_bss; struct ieee80211_key* iv_nw_keys; struct ieee80211com* iv_ic; } ;
struct ieee80211req_key {size_t ik_keyix; scalar_t__ ik_type; int ik_flags; scalar_t__ ik_keydata; scalar_t__ ik_keytsc; scalar_t__ ik_keyrsc; scalar_t__ ik_keylen; int /*<<< orphan*/  ik_macaddr; } ;
struct ieee80211req {int i_len; int /*<<< orphan*/  i_data; } ;
struct ieee80211com {int /*<<< orphan*/  ic_sta; } ;
struct ieee80211_key {int wk_flags; scalar_t__ wk_keyix; scalar_t__ wk_key; scalar_t__ wk_keylen; scalar_t__ wk_keytsc; scalar_t__* wk_keyrsc; struct ieee80211_cipher* wk_cipher; } ;
struct ieee80211_node {struct ieee80211_key ni_ucastkey; } ;
struct ieee80211_cipher {scalar_t__ ic_cipher; } ;
typedef  int /*<<< orphan*/  ik ;
struct TYPE_2__ {int /*<<< orphan*/  ni_macaddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_CIPHER_TKIP ; 
 scalar_t__ IEEE80211_KEYBUF_SIZE ; 
 size_t IEEE80211_KEYIX_NONE ; 
 int IEEE80211_KEY_DEFAULT ; 
 int IEEE80211_KEY_RECV ; 
 int IEEE80211_KEY_XMIT ; 
 scalar_t__ IEEE80211_MICBUF_SIZE ; 
 size_t IEEE80211_NONQOS_TID ; 
 size_t IEEE80211_WEP_NKID ; 
 int /*<<< orphan*/  PRIV_NET80211_GETKEY ; 
 int copyin (int /*<<< orphan*/ ,struct ieee80211req_key*,int) ; 
 int copyout (struct ieee80211req_key*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  curthread ; 
 struct ieee80211_node* ieee80211_find_vap_node (int /*<<< orphan*/ *,struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ priv_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ieee80211_ioctl_getkey(struct ieee80211vap *vap, struct ieee80211req *ireq)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_node *ni;
	struct ieee80211req_key ik;
	struct ieee80211_key *wk;
	const struct ieee80211_cipher *cip;
	u_int kid;
	int error;

	if (ireq->i_len != sizeof(ik))
		return EINVAL;
	error = copyin(ireq->i_data, &ik, sizeof(ik));
	if (error)
		return error;
	kid = ik.ik_keyix;
	if (kid == IEEE80211_KEYIX_NONE) {
		ni = ieee80211_find_vap_node(&ic->ic_sta, vap, ik.ik_macaddr);
		if (ni == NULL)
			return ENOENT;
		wk = &ni->ni_ucastkey;
	} else {
		if (kid >= IEEE80211_WEP_NKID)
			return EINVAL;
		wk = &vap->iv_nw_keys[kid];
		IEEE80211_ADDR_COPY(&ik.ik_macaddr, vap->iv_bss->ni_macaddr);
		ni = NULL;
	}
	cip = wk->wk_cipher;
	ik.ik_type = cip->ic_cipher;
	ik.ik_keylen = wk->wk_keylen;
	ik.ik_flags = wk->wk_flags & (IEEE80211_KEY_XMIT | IEEE80211_KEY_RECV);
	if (wk->wk_keyix == vap->iv_def_txkey)
		ik.ik_flags |= IEEE80211_KEY_DEFAULT;
	if (priv_check(curthread, PRIV_NET80211_GETKEY) == 0) {
		/* NB: only root can read key data */
		ik.ik_keyrsc = wk->wk_keyrsc[IEEE80211_NONQOS_TID];
		ik.ik_keytsc = wk->wk_keytsc;
		memcpy(ik.ik_keydata, wk->wk_key, wk->wk_keylen);
		if (cip->ic_cipher == IEEE80211_CIPHER_TKIP) {
			memcpy(ik.ik_keydata+wk->wk_keylen,
				wk->wk_key + IEEE80211_KEYBUF_SIZE,
				IEEE80211_MICBUF_SIZE);
			ik.ik_keylen += IEEE80211_MICBUF_SIZE;
		}
	} else {
		ik.ik_keyrsc = 0;
		ik.ik_keytsc = 0;
		memset(ik.ik_keydata, 0, sizeof(ik.ik_keydata));
	}
	if (ni != NULL)
		ieee80211_free_node(ni);
	return copyout(&ik, ireq->i_data, sizeof(ik));
}