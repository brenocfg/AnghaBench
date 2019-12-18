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
struct stge_softc {struct ifnet* sc_ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ CSR_READ_2 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ CSR_READ_4 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  STGE_FramesAbortXSColls ; 
 int /*<<< orphan*/  STGE_FramesLostRxErrors ; 
 int /*<<< orphan*/  STGE_FramesRcvdOk ; 
 int /*<<< orphan*/  STGE_FramesWEXDeferal ; 
 int /*<<< orphan*/  STGE_FramesXmtdOk ; 
 int /*<<< orphan*/  STGE_LOCK_ASSERT (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_LateCollisions ; 
 int /*<<< orphan*/  STGE_MultiColFrames ; 
 int /*<<< orphan*/  STGE_OctetRcvOk ; 
 int /*<<< orphan*/  STGE_OctetXmtdOk ; 
 int /*<<< orphan*/  STGE_SingleColFrames ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
stge_stats_update(struct stge_softc *sc)
{
	struct ifnet *ifp;

	STGE_LOCK_ASSERT(sc);

	ifp = sc->sc_ifp;

	CSR_READ_4(sc,STGE_OctetRcvOk);

	if_inc_counter(ifp, IFCOUNTER_IPACKETS, CSR_READ_4(sc, STGE_FramesRcvdOk));

	if_inc_counter(ifp, IFCOUNTER_IERRORS, CSR_READ_2(sc, STGE_FramesLostRxErrors));

	CSR_READ_4(sc, STGE_OctetXmtdOk);

	if_inc_counter(ifp, IFCOUNTER_OPACKETS, CSR_READ_4(sc, STGE_FramesXmtdOk));

	if_inc_counter(ifp, IFCOUNTER_COLLISIONS,
	    CSR_READ_4(sc, STGE_LateCollisions) +
	    CSR_READ_4(sc, STGE_MultiColFrames) +
	    CSR_READ_4(sc, STGE_SingleColFrames));

	if_inc_counter(ifp, IFCOUNTER_OERRORS,
	    CSR_READ_2(sc, STGE_FramesAbortXSColls) +
	    CSR_READ_2(sc, STGE_FramesWEXDeferal));
}