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
struct ieee80211com {scalar_t__ ic_curmode; } ;
struct rt2860_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ IEEE80211_M_STA ; 
 int /*<<< orphan*/  RAL_BARRIER_WRITE (struct rt2860_softc*) ; 
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2860_DEBUG ; 
 int RT2860_MAC_RX_EN ; 
 int RT2860_MAC_SRST ; 
 int /*<<< orphan*/  RT2860_MAC_SYS_CTRL ; 
 int RT2860_MAC_TX_EN ; 

__attribute__((used)) static void
rt2860_updatestats(struct rt2860_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	/*
	 * In IBSS or HostAP modes (when the hardware sends beacons), the
	 * MAC can run into a livelock and start sending CTS-to-self frames
	 * like crazy if protection is enabled.  Fortunately, we can detect
	 * when such a situation occurs and reset the MAC.
	 */
	if (ic->ic_curmode != IEEE80211_M_STA) {
		/* check if we're in a livelock situation.. */
		uint32_t tmp = RAL_READ(sc, RT2860_DEBUG);
		if ((tmp & (1 << 29)) && (tmp & (1 << 7 | 1 << 5))) {
			/* ..and reset MAC/BBP for a while.. */
			DPRINTF(("CTS-to-self livelock detected\n"));
			RAL_WRITE(sc, RT2860_MAC_SYS_CTRL, RT2860_MAC_SRST);
			RAL_BARRIER_WRITE(sc);
			DELAY(1);
			RAL_WRITE(sc, RT2860_MAC_SYS_CTRL,
			    RT2860_MAC_RX_EN | RT2860_MAC_TX_EN);
		}
	}
}