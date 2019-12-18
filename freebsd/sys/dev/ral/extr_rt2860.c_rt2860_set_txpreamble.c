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
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211com {int ic_flags; } ;
struct rt2860_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int IEEE80211_F_SHPREAMBLE ; 
 int /*<<< orphan*/  RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2860_AUTO_RSP_CFG ; 
 int /*<<< orphan*/  RT2860_CCK_SHORT_EN ; 

__attribute__((used)) static void
rt2860_set_txpreamble(struct rt2860_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t tmp;

	tmp = RAL_READ(sc, RT2860_AUTO_RSP_CFG);
	tmp &= ~RT2860_CCK_SHORT_EN;
	if (ic->ic_flags & IEEE80211_F_SHPREAMBLE)
		tmp |= RT2860_CCK_SHORT_EN;
	RAL_WRITE(sc, RT2860_AUTO_RSP_CFG, tmp);
}