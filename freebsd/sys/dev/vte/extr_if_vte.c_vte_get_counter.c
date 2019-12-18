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
struct vte_hw_stats {scalar_t__ rx_fifo_full; scalar_t__ rx_long_frames; scalar_t__ rx_runts; scalar_t__ rx_crcerrs; scalar_t__ rx_frames; scalar_t__ tx_underruns; scalar_t__ tx_late_colls; scalar_t__ tx_frames; } ;
struct vte_softc {struct vte_hw_stats vte_stats; } ;
struct ifnet {int dummy; } ;
typedef  int ift_counter ;

/* Variables and functions */
#define  IFCOUNTER_COLLISIONS 132 
#define  IFCOUNTER_IERRORS 131 
#define  IFCOUNTER_IPACKETS 130 
#define  IFCOUNTER_OERRORS 129 
#define  IFCOUNTER_OPACKETS 128 
 scalar_t__ if_get_counter_default (struct ifnet*,int) ; 
 struct vte_softc* if_getsoftc (struct ifnet*) ; 

__attribute__((used)) static uint64_t
vte_get_counter(struct ifnet *ifp, ift_counter cnt)
{
	struct vte_softc *sc;
	struct vte_hw_stats *stat;

	sc = if_getsoftc(ifp);
	stat = &sc->vte_stats;

	switch (cnt) {
	case IFCOUNTER_OPACKETS:
		return (stat->tx_frames);
	case IFCOUNTER_COLLISIONS:
		return (stat->tx_late_colls);
	case IFCOUNTER_OERRORS:
		return (stat->tx_late_colls + stat->tx_underruns);
	case IFCOUNTER_IPACKETS:
		return (stat->rx_frames);
	case IFCOUNTER_IERRORS:
		return (stat->rx_crcerrs + stat->rx_runts +
		    stat->rx_long_frames + stat->rx_fifo_full);
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}