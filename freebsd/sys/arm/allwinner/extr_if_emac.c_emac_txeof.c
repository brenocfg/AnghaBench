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
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct emac_softc {int emac_fifo_mask; scalar_t__ emac_watchdog_timer; struct ifnet* emac_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_ASSERT_LOCKED (struct emac_softc*) ; 
 int EMAC_TX_FIFO0 ; 
 int EMAC_TX_FIFO1 ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
emac_txeof(struct emac_softc *sc, uint32_t status)
{
	struct ifnet *ifp;

	EMAC_ASSERT_LOCKED(sc);

	ifp = sc->emac_ifp;
	status &= (EMAC_TX_FIFO0 | EMAC_TX_FIFO1);
	sc->emac_fifo_mask &= ~status;
	if (status == (EMAC_TX_FIFO0 | EMAC_TX_FIFO1))
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 2);
	else
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	/* Unarm watchdog timer if no TX */
	sc->emac_watchdog_timer = 0;
}