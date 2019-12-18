#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mwl_vap {int /*<<< orphan*/  mv_hvap; int /*<<< orphan*/  mv_eapolformat; } ;
struct ieee80211vap {scalar_t__ iv_state; struct ieee80211_node* iv_bss; } ;
struct ieee80211_txparam {scalar_t__ ucastrate; int /*<<< orphan*/  mcastrate; int /*<<< orphan*/  mgmtrate; } ;
struct ieee80211_node {struct ieee80211_txparam* ni_txparms; } ;
typedef  int /*<<< orphan*/  rates ;
struct TYPE_4__ {int /*<<< orphan*/  MgtRate; int /*<<< orphan*/  McastRate; } ;
typedef  TYPE_1__ MWL_HAL_TXRATE ;

/* Variables and functions */
 scalar_t__ IEEE80211_FIXED_RATE_NONE ; 
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct mwl_vap* MWL_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  RATE_AUTO ; 
 int /*<<< orphan*/  RATE_FIXED ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwl_calcformat (int /*<<< orphan*/ ,struct ieee80211_node*) ; 
 int mwl_hal_settxrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
mwl_setrates(struct ieee80211vap *vap)
{
	struct mwl_vap *mvp = MWL_VAP(vap);
	struct ieee80211_node *ni = vap->iv_bss;
	const struct ieee80211_txparam *tp = ni->ni_txparms;
	MWL_HAL_TXRATE rates;

	KASSERT(vap->iv_state == IEEE80211_S_RUN, ("state %d", vap->iv_state));

	/*
	 * Update the h/w rate map.
	 * NB: 0x80 for MCS is passed through unchanged
	 */
	memset(&rates, 0, sizeof(rates));
	/* rate used to send management frames */
	rates.MgtRate = tp->mgmtrate;
	/* rate used to send multicast frames */
	rates.McastRate = tp->mcastrate;

	/* while here calculate EAPOL fixed rate cookie */
	mvp->mv_eapolformat = htole16(mwl_calcformat(rates.MgtRate, ni));

	return mwl_hal_settxrate(mvp->mv_hvap,
	    tp->ucastrate != IEEE80211_FIXED_RATE_NONE ?
		RATE_FIXED : RATE_AUTO, &rates);
}