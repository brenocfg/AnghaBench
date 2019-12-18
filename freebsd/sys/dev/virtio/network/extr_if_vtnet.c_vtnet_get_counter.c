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
typedef  int /*<<< orphan*/  uint64_t ;
struct vtnet_txq_stats {int /*<<< orphan*/  vtxs_omcasts; int /*<<< orphan*/  vtxs_obytes; int /*<<< orphan*/  vtxs_opackets; } ;
struct vtnet_softc {int dummy; } ;
struct vtnet_rxq_stats {int /*<<< orphan*/  vrxs_ierrors; int /*<<< orphan*/  vrxs_iqdrops; int /*<<< orphan*/  vrxs_ipackets; } ;
typedef  int ift_counter ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
#define  IFCOUNTER_IERRORS 133 
#define  IFCOUNTER_IPACKETS 132 
#define  IFCOUNTER_IQDROPS 131 
#define  IFCOUNTER_OBYTES 130 
#define  IFCOUNTER_OMCASTS 129 
#define  IFCOUNTER_OPACKETS 128 
 int /*<<< orphan*/  if_get_counter_default (int /*<<< orphan*/ ,int) ; 
 struct vtnet_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtnet_accum_stats (struct vtnet_softc*,struct vtnet_rxq_stats*,struct vtnet_txq_stats*) ; 

__attribute__((used)) static uint64_t
vtnet_get_counter(if_t ifp, ift_counter cnt)
{
	struct vtnet_softc *sc;
	struct vtnet_rxq_stats rxaccum;
	struct vtnet_txq_stats txaccum;

	sc = if_getsoftc(ifp);
	vtnet_accum_stats(sc, &rxaccum, &txaccum);

	switch (cnt) {
	case IFCOUNTER_IPACKETS:
		return (rxaccum.vrxs_ipackets);
	case IFCOUNTER_IQDROPS:
		return (rxaccum.vrxs_iqdrops);
	case IFCOUNTER_IERRORS:
		return (rxaccum.vrxs_ierrors);
	case IFCOUNTER_OPACKETS:
		return (txaccum.vtxs_opackets);
#ifndef VTNET_LEGACY_TX
	case IFCOUNTER_OBYTES:
		return (txaccum.vtxs_obytes);
	case IFCOUNTER_OMCASTS:
		return (txaccum.vtxs_omcasts);
#endif
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}