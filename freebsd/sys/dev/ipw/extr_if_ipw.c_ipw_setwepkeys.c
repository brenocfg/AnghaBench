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
struct ipw_wep_key {int idx; int /*<<< orphan*/  len; int /*<<< orphan*/  key; } ;
struct ieee80211com {int /*<<< orphan*/  ic_vaps; } ;
struct ipw_softc {struct ieee80211com sc_ic; } ;
struct ieee80211vap {struct ieee80211_key* iv_nw_keys; } ;
struct ieee80211_key {int /*<<< orphan*/  wk_keylen; int /*<<< orphan*/  wk_key; TYPE_1__* wk_cipher; } ;
struct TYPE_2__ {scalar_t__ ic_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ IEEE80211_CIPHER_WEP ; 
 int IEEE80211_WEP_NKID ; 
 int /*<<< orphan*/  IPW_CMD_SET_WEP_KEY ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int ipw_cmd (struct ipw_softc*,int /*<<< orphan*/ ,struct ipw_wep_key*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ipw_setwepkeys(struct ipw_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	struct ipw_wep_key wepkey;
	struct ieee80211_key *wk;
	int error, i;

	for (i = 0; i < IEEE80211_WEP_NKID; i++) {
		wk = &vap->iv_nw_keys[i];

		if (wk->wk_cipher == NULL ||
		    wk->wk_cipher->ic_cipher != IEEE80211_CIPHER_WEP)
			continue;

		wepkey.idx = i;
		wepkey.len = wk->wk_keylen;
		memset(wepkey.key, 0, sizeof wepkey.key);
		memcpy(wepkey.key, wk->wk_key, wk->wk_keylen);
		DPRINTF(("Setting wep key index %u len %u\n", wepkey.idx,
		    wepkey.len));
		error = ipw_cmd(sc, IPW_CMD_SET_WEP_KEY, &wepkey,
		    sizeof wepkey);
		if (error != 0)
			return error;
	}
	return 0;
}