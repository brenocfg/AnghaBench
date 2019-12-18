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
typedef  int /*<<< orphan*/  uint8_t ;
struct nf10bmac_softc {int /*<<< orphan*/  nf10bmac_tick; struct ifnet* nf10bmac_ifp; int /*<<< orphan*/  nf10bmac_flags; int /*<<< orphan*/  nf10bmac_eth_addr; } ;
struct ifnet {int if_drv_flags; int if_capenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/ * IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  NF10BMAC_FLAGS_LINK ; 
 int /*<<< orphan*/  NF10BMAC_LOCK_ASSERT (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_RX_INTR_CLEAR_DIS (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  NF10BMAC_RX_INTR_ENABLE (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf10bmac_eat_packet_munch_munch (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  nf10bmac_reset (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  nf10bmac_stop_locked (struct nf10bmac_softc*) ; 
 int /*<<< orphan*/  nf10bmac_tick ; 

__attribute__((used)) static void
nf10bmac_init_locked(struct nf10bmac_softc *sc)
{
	struct ifnet *ifp;
	uint8_t *eaddr;

	NF10BMAC_LOCK_ASSERT(sc);
	ifp = sc->nf10bmac_ifp;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	/*
	 * Must update the ether address if changed.  Given we do not handle
	 * in nf10bmac_ioctl() but it's in the general framework, just always
	 * do it here before nf10bmac_reset().
	 */
	eaddr = IF_LLADDR(sc->nf10bmac_ifp);
	bcopy(eaddr, &sc->nf10bmac_eth_addr, ETHER_ADDR_LEN);
	/* XXX-BZ we do not have any way to tell the NIC our ether address. */

	/* Make things frind to halt, cleanup, ... */
	nf10bmac_stop_locked(sc);
	/* ... reset, ... */
	nf10bmac_reset(sc);

	/* Memory rings?  DMA engine? MC filter?  MII? */
	/* Instead drain the FIFO; or at least a possible first packet.. */
	nf10bmac_eat_packet_munch_munch(sc);

#ifdef DEVICE_POLLING
	/* Only enable interrupts if we are not polling. */
	if (ifp->if_capenable & IFCAP_POLLING) {
		NF10BMAC_RX_INTR_CLEAR_DIS(sc);
	} else
#endif
	{
		NF10BMAC_RX_INTR_ENABLE(sc);
	}

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	/* We have no underlying media, fake link state. */
	sc->nf10bmac_flags = NF10BMAC_FLAGS_LINK;	/* Always up. */
	if_link_state_change(sc->nf10bmac_ifp, LINK_STATE_UP);

#ifdef ENABLE_WATCHDOG
	callout_reset(&sc->nf10bmac_tick, hz, nf10bmac_tick, sc);
#endif
}