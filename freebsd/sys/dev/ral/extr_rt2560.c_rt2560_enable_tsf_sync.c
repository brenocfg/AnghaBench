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
typedef  int uint16_t ;
struct ieee80211com {scalar_t__ ic_opmode; int /*<<< orphan*/  ic_vaps; } ;
struct rt2560_softc {struct ieee80211com sc_ic; } ;
struct ieee80211vap {scalar_t__ iv_opmode; TYPE_1__* iv_bss; } ;
struct TYPE_2__ {int ni_intval; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct rt2560_softc*,char*,char*) ; 
 scalar_t__ IEEE80211_M_STA ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2560_BCNOCSR ; 
 int /*<<< orphan*/  RT2560_CSR12 ; 
 int /*<<< orphan*/  RT2560_CSR13 ; 
 int /*<<< orphan*/  RT2560_CSR14 ; 
 int RT2560_ENABLE_BEACON_GENERATOR ; 
 int RT2560_ENABLE_TBCN ; 
 int RT2560_ENABLE_TSF ; 
 int RT2560_ENABLE_TSF_SYNC (int) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt2560_enable_tsf_sync(struct rt2560_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	uint16_t logcwmin, preload;
	uint32_t tmp;

	/* first, disable TSF synchronization */
	RAL_WRITE(sc, RT2560_CSR14, 0);

	tmp = 16 * vap->iv_bss->ni_intval;
	RAL_WRITE(sc, RT2560_CSR12, tmp);

	RAL_WRITE(sc, RT2560_CSR13, 0);

	logcwmin = 5;
	preload = (vap->iv_opmode == IEEE80211_M_STA) ? 384 : 1024;
	tmp = logcwmin << 16 | preload;
	RAL_WRITE(sc, RT2560_BCNOCSR, tmp);

	/* finally, enable TSF synchronization */
	tmp = RT2560_ENABLE_TSF | RT2560_ENABLE_TBCN;
	if (ic->ic_opmode == IEEE80211_M_STA)
		tmp |= RT2560_ENABLE_TSF_SYNC(1);
	else
		tmp |= RT2560_ENABLE_TSF_SYNC(2) |
		       RT2560_ENABLE_BEACON_GENERATOR;
	RAL_WRITE(sc, RT2560_CSR14, tmp);

	DPRINTF(sc, "%s", "enabling TSF synchronization\n");
}