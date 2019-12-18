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
typedef  int /*<<< orphan*/  uint16_t ;
struct stge_softc {struct ifnet* sc_ifp; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_2 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct stge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  RM_ReceiveAllFrames ; 
 int /*<<< orphan*/  RM_ReceiveBroadcast ; 
 int /*<<< orphan*/  RM_ReceiveUnicast ; 
 int /*<<< orphan*/  STGE_LOCK_ASSERT (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_ReceiveMode ; 

__attribute__((used)) static void
stge_set_filter(struct stge_softc *sc)
{
	struct ifnet *ifp;
	uint16_t mode;

	STGE_LOCK_ASSERT(sc);

	ifp = sc->sc_ifp;

	mode = CSR_READ_2(sc, STGE_ReceiveMode);
	mode |= RM_ReceiveUnicast;
	if ((ifp->if_flags & IFF_BROADCAST) != 0)
		mode |= RM_ReceiveBroadcast;
	else
		mode &= ~RM_ReceiveBroadcast;
	if ((ifp->if_flags & IFF_PROMISC) != 0)
		mode |= RM_ReceiveAllFrames;
	else
		mode &= ~RM_ReceiveAllFrames;

	CSR_WRITE_2(sc, STGE_ReceiveMode, mode);
}