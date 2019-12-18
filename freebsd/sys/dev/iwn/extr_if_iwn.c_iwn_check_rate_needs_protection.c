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
struct iwn_softc {int dummy; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {int ic_flags; int /*<<< orphan*/  ic_rt; int /*<<< orphan*/  ic_curchan; } ;

/* Variables and functions */
 int IEEE80211_F_USEPROT ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 int IEEE80211_RATE_MCS ; 
 scalar_t__ IEEE80211_T_CCK ; 
 scalar_t__ ieee80211_rate2phytype (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwn_check_rate_needs_protection(struct iwn_softc *sc,
    struct ieee80211vap *vap, uint8_t rate)
{
	struct ieee80211com *ic = vap->iv_ic;

	/*
	 * Not in 2GHz mode? Then there's no need to enable OFDM
	 * 11bg protection.
	 */
	if (! IEEE80211_IS_CHAN_2GHZ(ic->ic_curchan)) {
		return (0);
	}

	/*
	 * 11bg protection not enabled? Then don't use it.
	 */
	if ((ic->ic_flags & IEEE80211_F_USEPROT) == 0)
		return (0);

	/*
	 * If it's an 11n rate - no protection.
	 * We'll do it via a specific 11n check.
	 */
	if (rate & IEEE80211_RATE_MCS) {
		return (0);
	}

	/*
	 * Do a rate table lookup.  If the PHY is CCK,
	 * don't do protection.
	 */
	if (ieee80211_rate2phytype(ic->ic_rt, rate) == IEEE80211_T_CCK)
		return (0);

	/*
	 * Yup, enable protection.
	 */
	return (1);
}