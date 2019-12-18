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
struct mxge_softc {int num_slices; TYPE_3__* ss; } ;
struct ifnet {int dummy; } ;
typedef  int ift_counter ;
struct TYPE_5__ {TYPE_1__* br; } ;
struct TYPE_6__ {TYPE_2__ tx; int /*<<< orphan*/  omcasts; int /*<<< orphan*/  obytes; int /*<<< orphan*/  oerrors; int /*<<< orphan*/  opackets; int /*<<< orphan*/  ipackets; } ;
struct TYPE_4__ {int /*<<< orphan*/  br_drops; } ;

/* Variables and functions */
#define  IFCOUNTER_IPACKETS 133 
#define  IFCOUNTER_OBYTES 132 
#define  IFCOUNTER_OERRORS 131 
#define  IFCOUNTER_OMCASTS 130 
#define  IFCOUNTER_OPACKETS 129 
#define  IFCOUNTER_OQDROPS 128 
 scalar_t__ if_get_counter_default (struct ifnet*,int) ; 
 struct mxge_softc* if_getsoftc (struct ifnet*) ; 

__attribute__((used)) static uint64_t
mxge_get_counter(struct ifnet *ifp, ift_counter cnt)
{
	struct mxge_softc *sc;
	uint64_t rv;

	sc = if_getsoftc(ifp);
	rv = 0;

	switch (cnt) {
	case IFCOUNTER_IPACKETS:
		for (int s = 0; s < sc->num_slices; s++)
			rv += sc->ss[s].ipackets;
		return (rv);
	case IFCOUNTER_OPACKETS:
		for (int s = 0; s < sc->num_slices; s++)
			rv += sc->ss[s].opackets;
		return (rv);
	case IFCOUNTER_OERRORS:
		for (int s = 0; s < sc->num_slices; s++)
			rv += sc->ss[s].oerrors;
		return (rv);
#ifdef IFNET_BUF_RING
	case IFCOUNTER_OBYTES:
		for (int s = 0; s < sc->num_slices; s++)
			rv += sc->ss[s].obytes;
		return (rv);
	case IFCOUNTER_OMCASTS:
		for (int s = 0; s < sc->num_slices; s++)
			rv += sc->ss[s].omcasts;
		return (rv);
	case IFCOUNTER_OQDROPS:
		for (int s = 0; s < sc->num_slices; s++)
			rv += sc->ss[s].tx.br->br_drops;
		return (rv);
#endif
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}