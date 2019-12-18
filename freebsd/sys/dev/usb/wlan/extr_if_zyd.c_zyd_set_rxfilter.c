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
struct ieee80211com {int ic_opmode; } ;
struct zyd_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IEEE80211_M_HOSTAP 131 
#define  IEEE80211_M_IBSS 130 
#define  IEEE80211_M_MONITOR 129 
#define  IEEE80211_M_STA 128 
 int /*<<< orphan*/  ZYD_FILTER_BSS ; 
 int /*<<< orphan*/  ZYD_FILTER_HOSTAP ; 
 int /*<<< orphan*/  ZYD_FILTER_MONITOR ; 
 int /*<<< orphan*/  ZYD_MAC_RXFILTER ; 
 int zyd_write32 (struct zyd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zyd_set_rxfilter(struct zyd_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t rxfilter;

	switch (ic->ic_opmode) {
	case IEEE80211_M_STA:
		rxfilter = ZYD_FILTER_BSS;
		break;
	case IEEE80211_M_IBSS:
	case IEEE80211_M_HOSTAP:
		rxfilter = ZYD_FILTER_HOSTAP;
		break;
	case IEEE80211_M_MONITOR:
		rxfilter = ZYD_FILTER_MONITOR;
		break;
	default:
		/* should not get there */
		return (EINVAL);
	}
	return zyd_write32(sc, ZYD_MAC_RXFILTER, rxfilter);
}