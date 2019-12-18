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
struct ieee80211vap {scalar_t__ iv_csa_count; struct ieee80211com* iv_ic; } ;
struct ieee80211com {scalar_t__ ic_csa_count; int /*<<< orphan*/  ic_csa_newchan; } ;
struct ieee80211_csa_ie {int csa_len; int csa_mode; scalar_t__ csa_count; int /*<<< orphan*/  csa_newchan; int /*<<< orphan*/  csa_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ELEMID_CSA ; 
 int /*<<< orphan*/  ieee80211_chan2ieee (struct ieee80211com*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t *
ieee80211_add_csa(uint8_t *frm, struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_csa_ie *csa = (struct ieee80211_csa_ie *) frm;

	csa->csa_ie = IEEE80211_ELEMID_CSA;
	csa->csa_len = 3;
	csa->csa_mode = 1;		/* XXX force quiet on channel */
	csa->csa_newchan = ieee80211_chan2ieee(ic, ic->ic_csa_newchan);
	csa->csa_count = ic->ic_csa_count - vap->iv_csa_count;
	return frm + sizeof(*csa);
}