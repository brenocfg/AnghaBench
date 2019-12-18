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
typedef  int uint16_t ;
struct ieee80211com {scalar_t__ ic_opmode; int /*<<< orphan*/  ic_vaps; } ;
struct ural_softc {struct ieee80211com sc_ic; } ;
struct ieee80211vap {TYPE_1__* iv_bss; } ;
struct TYPE_2__ {int ni_intval; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 scalar_t__ IEEE80211_M_STA ; 
 int RAL_ENABLE_BEACON_GENERATOR ; 
 int RAL_ENABLE_TBCN ; 
 int RAL_ENABLE_TSF ; 
 int RAL_ENABLE_TSF_SYNC (int) ; 
 int /*<<< orphan*/  RAL_TXRX_CSR18 ; 
 int /*<<< orphan*/  RAL_TXRX_CSR19 ; 
 int /*<<< orphan*/  RAL_TXRX_CSR20 ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ural_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ural_enable_tsf_sync(struct ural_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	uint16_t logcwmin, preload, tmp;

	/* first, disable TSF synchronization */
	ural_write(sc, RAL_TXRX_CSR19, 0);

	tmp = (16 * vap->iv_bss->ni_intval) << 4;
	ural_write(sc, RAL_TXRX_CSR18, tmp);

	logcwmin = (ic->ic_opmode == IEEE80211_M_IBSS) ? 2 : 0;
	preload = (ic->ic_opmode == IEEE80211_M_IBSS) ? 320 : 6;
	tmp = logcwmin << 12 | preload;
	ural_write(sc, RAL_TXRX_CSR20, tmp);

	/* finally, enable TSF synchronization */
	tmp = RAL_ENABLE_TSF | RAL_ENABLE_TBCN;
	if (ic->ic_opmode == IEEE80211_M_STA)
		tmp |= RAL_ENABLE_TSF_SYNC(1);
	else
		tmp |= RAL_ENABLE_TSF_SYNC(2) | RAL_ENABLE_BEACON_GENERATOR;
	ural_write(sc, RAL_TXRX_CSR19, tmp);

	DPRINTF("enabling TSF synchronization\n");
}