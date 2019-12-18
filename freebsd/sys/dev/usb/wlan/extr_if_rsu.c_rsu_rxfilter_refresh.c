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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct ieee80211com {scalar_t__ ic_opmode; scalar_t__ ic_promisc; } ;
struct rsu_softc {scalar_t__ sc_vap_is_running; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_MONITOR ; 
 int R92S_RCR_AAP ; 
 int R92S_RCR_ACF ; 
 int R92S_RCR_ADF ; 
 int R92S_RCR_APM ; 
 int R92S_RCR_CBSSID ; 
 int /*<<< orphan*/  R92S_RXFLTMAP_MGT ; 
 scalar_t__ R92S_RXFLTMAP_MGT_DEF ; 
 int /*<<< orphan*/  RSU_ASSERT_LOCKED (struct rsu_softc*) ; 
 int /*<<< orphan*/  rsu_rxfilter_set (struct rsu_softc*,int,int) ; 
 int /*<<< orphan*/  rsu_write_2 (struct rsu_softc*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
rsu_rxfilter_refresh(struct rsu_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t mask_all, mask_min;

	RSU_ASSERT_LOCKED(sc);

	/* NB: RCR_AMF / RXFLTMAP_MGT are used by firmware. */
	mask_all = R92S_RCR_ACF | R92S_RCR_AAP;
	mask_min = R92S_RCR_APM;
	if (sc->sc_vap_is_running)
		mask_min |= R92S_RCR_CBSSID;
	else
		mask_all |= R92S_RCR_ADF;

	if (ic->ic_opmode == IEEE80211_M_MONITOR) {
		uint16_t rxfltmap;
		if (sc->sc_vap_is_running)
			rxfltmap = 0;
		else
			rxfltmap = R92S_RXFLTMAP_MGT_DEF;
		rsu_write_2(sc, R92S_RXFLTMAP_MGT, rxfltmap);
	}

	if (ic->ic_promisc == 0 && ic->ic_opmode != IEEE80211_M_MONITOR)
		rsu_rxfilter_set(sc, mask_all, mask_min);
	else
		rsu_rxfilter_set(sc, mask_min, mask_all);
}