#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct ti_stats {scalar_t__ dot3StatsLateCollisions; scalar_t__ dot3StatsExcessiveCollisions; scalar_t__ dot3StatsMultipleCollisionFrames; scalar_t__ dot3StatsSingleCollisionFrames; } ;
struct TYPE_5__ {int /*<<< orphan*/  ti_gib_map; int /*<<< orphan*/  ti_gib_tag; } ;
struct TYPE_4__ {TYPE_3__* ti_info; } ;
struct ti_softc {TYPE_2__ ti_cdata; TYPE_1__ ti_rdata; } ;
struct ifnet {int dummy; } ;
typedef  int ift_counter ;
struct TYPE_6__ {struct ti_stats ti_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
#define  IFCOUNTER_COLLISIONS 128 
 int /*<<< orphan*/  TI_LOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  TI_UNLOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ if_get_counter_default (struct ifnet*,int) ; 
 struct ti_softc* if_getsoftc (struct ifnet*) ; 

__attribute__((used)) static uint64_t
ti_get_counter(struct ifnet *ifp, ift_counter cnt)
{

	switch (cnt) {
	case IFCOUNTER_COLLISIONS:
	    {
		struct ti_softc *sc;
		struct ti_stats *s;
		uint64_t rv;

		sc = if_getsoftc(ifp);
		s = &sc->ti_rdata.ti_info->ti_stats;

		TI_LOCK(sc);
		bus_dmamap_sync(sc->ti_cdata.ti_gib_tag,
		    sc->ti_cdata.ti_gib_map, BUS_DMASYNC_POSTREAD);
		rv = s->dot3StatsSingleCollisionFrames +
		    s->dot3StatsMultipleCollisionFrames +
		    s->dot3StatsExcessiveCollisions +
		    s->dot3StatsLateCollisions;
		bus_dmamap_sync(sc->ti_cdata.ti_gib_tag,
		    sc->ti_cdata.ti_gib_map, BUS_DMASYNC_PREREAD);
		TI_UNLOCK(sc);
		return (rv);
	    }
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}