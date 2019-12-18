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
struct run_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int IEEE80211_F_SHPREAMBLE ; 
 int /*<<< orphan*/  RT2860_AUTO_RSP_CFG ; 
 int /*<<< orphan*/  RT2860_CCK_SHORT_EN ; 
 int /*<<< orphan*/  run_read (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_set_txpreamble(struct run_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t tmp;

	run_read(sc, RT2860_AUTO_RSP_CFG, &tmp);
	if (ic->ic_flags & IEEE80211_F_SHPREAMBLE)
		tmp |= RT2860_CCK_SHORT_EN;
	else
		tmp &= ~RT2860_CCK_SHORT_EN;
	run_write(sc, RT2860_AUTO_RSP_CFG, tmp);
}