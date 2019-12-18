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
struct iwi_wep_key {int idx; int /*<<< orphan*/  len; int /*<<< orphan*/  key; int /*<<< orphan*/  cmd; } ;
struct iwi_softc {int dummy; } ;
struct ieee80211vap {struct ieee80211_key* iv_nw_keys; } ;
struct ieee80211_key {int /*<<< orphan*/  wk_keylen; int /*<<< orphan*/  wk_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int IEEE80211_WEP_NKID ; 
 int /*<<< orphan*/  IWI_CMD_SET_WEP_KEY ; 
 int /*<<< orphan*/  IWI_WEP_KEY_CMD_SETKEY ; 
 int iwi_cmd (struct iwi_softc*,int /*<<< orphan*/ ,struct iwi_wep_key*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwi_setwepkeys(struct iwi_softc *sc, struct ieee80211vap *vap)
{
	struct iwi_wep_key wepkey;
	struct ieee80211_key *wk;
	int error, i;

	for (i = 0; i < IEEE80211_WEP_NKID; i++) {
		wk = &vap->iv_nw_keys[i];

		wepkey.cmd = IWI_WEP_KEY_CMD_SETKEY;
		wepkey.idx = i;
		wepkey.len = wk->wk_keylen;
		memset(wepkey.key, 0, sizeof wepkey.key);
		memcpy(wepkey.key, wk->wk_key, wk->wk_keylen);
		DPRINTF(("Setting wep key index %u len %u\n", wepkey.idx,
		    wepkey.len));
		error = iwi_cmd(sc, IWI_CMD_SET_WEP_KEY, &wepkey,
		    sizeof wepkey);
		if (error != 0)
			return error;
	}
	return 0;
}