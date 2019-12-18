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
typedef  scalar_t__ uint64_t ;
struct ifnet {int dummy; } ;
struct et_hw_stats {scalar_t__ rx_drop; scalar_t__ rx_jabbers; scalar_t__ rx_runts; scalar_t__ rx_cserrs; scalar_t__ rx_codeerrs; scalar_t__ rx_lenerrs; scalar_t__ rx_alignerrs; scalar_t__ rx_crcerrs; scalar_t__ rx_frames; scalar_t__ tx_late_colls; scalar_t__ tx_excess_deferred; scalar_t__ tx_crcerrs; scalar_t__ tx_jabbers; scalar_t__ tx_drop; scalar_t__ tx_total_colls; scalar_t__ tx_frames; } ;
struct et_softc {struct et_hw_stats sc_stats; } ;
typedef  int ift_counter ;

/* Variables and functions */
#define  IFCOUNTER_COLLISIONS 132 
#define  IFCOUNTER_IERRORS 131 
#define  IFCOUNTER_IPACKETS 130 
#define  IFCOUNTER_OERRORS 129 
#define  IFCOUNTER_OPACKETS 128 
 scalar_t__ if_get_counter_default (struct ifnet*,int) ; 
 struct et_softc* if_getsoftc (struct ifnet*) ; 

__attribute__((used)) static uint64_t
et_get_counter(struct ifnet *ifp, ift_counter cnt)
{
	struct et_softc *sc;
	struct et_hw_stats *stats;

	sc = if_getsoftc(ifp);
	stats = &sc->sc_stats;

	switch (cnt) {
	case IFCOUNTER_OPACKETS:
		return (stats->tx_frames);
	case IFCOUNTER_COLLISIONS:
		return (stats->tx_total_colls);
	case IFCOUNTER_OERRORS:
		return (stats->tx_drop + stats->tx_jabbers +
		    stats->tx_crcerrs + stats->tx_excess_deferred +
		    stats->tx_late_colls);
	case IFCOUNTER_IPACKETS:
		return (stats->rx_frames);
	case IFCOUNTER_IERRORS:
		return (stats->rx_crcerrs + stats->rx_alignerrs +
		    stats->rx_lenerrs + stats->rx_codeerrs + stats->rx_cserrs +
		    stats->rx_runts + stats->rx_jabbers + stats->rx_drop);
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}