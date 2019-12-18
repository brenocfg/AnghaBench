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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211com {scalar_t__ ic_countryie_chan; scalar_t__ ic_bsschan; int /*<<< orphan*/ * ic_countryie; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_80211_NODE_IE ; 
 int /*<<< orphan*/ * add_appie (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ieee80211_alloc_countryie (struct ieee80211com*) ; 

__attribute__((used)) static uint8_t *
ieee80211_add_countryie(uint8_t *frm, struct ieee80211com *ic)
{

	if (ic->ic_countryie == NULL ||
	    ic->ic_countryie_chan != ic->ic_bsschan) {
		/*
		 * Handle lazy construction of ie.  This is done on
		 * first use and after a channel change that requires
		 * re-calculation.
		 */
		if (ic->ic_countryie != NULL)
			IEEE80211_FREE(ic->ic_countryie, M_80211_NODE_IE);
		ic->ic_countryie = ieee80211_alloc_countryie(ic);
		if (ic->ic_countryie == NULL)
			return frm;
		ic->ic_countryie_chan = ic->ic_bsschan;
	}
	return add_appie(frm, ic->ic_countryie);
}