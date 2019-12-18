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
struct rt2560_tx_data {int /*<<< orphan*/ * ni; int /*<<< orphan*/  m; int /*<<< orphan*/  map; } ;
struct TYPE_2__ {size_t next; int /*<<< orphan*/  data_dmat; struct rt2560_tx_data* data; } ;
struct ieee80211com {scalar_t__ ic_opmode; } ;
struct rt2560_softc {TYPE_1__ bcnq; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  DPRINTFN (struct rt2560_softc*,int,char*,char*) ; 
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 int RT2560_BEACON_RING_COUNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_beacon_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2560_tx_bcn (struct rt2560_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt2560_beacon_expire(struct rt2560_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct rt2560_tx_data *data;

	if (ic->ic_opmode != IEEE80211_M_IBSS &&
	    ic->ic_opmode != IEEE80211_M_HOSTAP &&
	    ic->ic_opmode != IEEE80211_M_MBSS)
		return;	

	data = &sc->bcnq.data[sc->bcnq.next];
	/*
	 * Don't send beacon if bsschan isn't set
	 */
	if (data->ni == NULL)
	        return;

	bus_dmamap_sync(sc->bcnq.data_dmat, data->map, BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(sc->bcnq.data_dmat, data->map);

	/* XXX 1 =>'s mcast frames which means all PS sta's will wakeup! */
	ieee80211_beacon_update(data->ni, data->m, 1);

	rt2560_tx_bcn(sc, data->m, data->ni);

	DPRINTFN(sc, 15, "%s", "beacon expired\n");

	sc->bcnq.next = (sc->bcnq.next + 1) % RT2560_BEACON_RING_COUNT;
}