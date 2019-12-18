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
typedef  int uint32_t ;
struct ieee80211com {int ic_flags; scalar_t__ ic_protmode; int /*<<< orphan*/  ic_curchan; } ;
struct rt2860_softc {struct ieee80211com sc_ic; } ;
struct TYPE_2__ {int mcs; } ;

/* Variables and functions */
 int IEEE80211_F_USEPROT ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_PROT_CTSONLY ; 
 scalar_t__ IEEE80211_PROT_RTSCTS ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2860_CCK_PROT_CFG ; 
 int /*<<< orphan*/  RT2860_OFDM_PROT_CFG ; 
 int RT2860_PROT_CTRL_CTS ; 
 int RT2860_PROT_CTRL_RTS_CTS ; 
 int RT2860_PROT_NAV_SHORT ; 
 size_t RT2860_RIDX_CCK11 ; 
 size_t RT2860_RIDX_OFDM6 ; 
 int RT2860_RTSTH_EN ; 
 int RT2860_TXOP_ALLOW_ALL ; 
 TYPE_1__* rt2860_rates ; 

__attribute__((used)) static void
rt2860_updateprot(struct rt2860_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t tmp;

	tmp = RT2860_RTSTH_EN | RT2860_PROT_NAV_SHORT | RT2860_TXOP_ALLOW_ALL;
	/* setup protection frame rate (MCS code) */
	tmp |= IEEE80211_IS_CHAN_5GHZ(ic->ic_curchan) ?
	    rt2860_rates[RT2860_RIDX_OFDM6].mcs :
	    rt2860_rates[RT2860_RIDX_CCK11].mcs;

	/* CCK frames don't require protection */
	RAL_WRITE(sc, RT2860_CCK_PROT_CFG, tmp);

	if (ic->ic_flags & IEEE80211_F_USEPROT) {
		if (ic->ic_protmode == IEEE80211_PROT_RTSCTS)
			tmp |= RT2860_PROT_CTRL_RTS_CTS;
		else if (ic->ic_protmode == IEEE80211_PROT_CTSONLY)
			tmp |= RT2860_PROT_CTRL_CTS;
	}
	RAL_WRITE(sc, RT2860_OFDM_PROT_CFG, tmp);
}