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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  nge_tx_ring_paddr; int /*<<< orphan*/  nge_rx_ring_paddr; } ;
struct nge_softc {int nge_int_holdoff; int /*<<< orphan*/  nge_stat_ch; scalar_t__ nge_watchdog_timer; int /*<<< orphan*/  nge_flags; TYPE_1__ nge_rdata; int /*<<< orphan*/  nge_dev; struct ifnet* nge_ifp; int /*<<< orphan*/  nge_miibus; } ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; int if_capenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  CSR_BARRIER_4 (struct nge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct nge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct nge_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ENOBUFS ; 
 int IFCAP_POLLING ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int* IF_LLADDR (struct ifnet*) ; 
 int NGE_ADDR_HI (int /*<<< orphan*/ ) ; 
 int NGE_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGE_CFG ; 
 int NGE_CFG_EXTSTS_ENB ; 
 int NGE_CFG_PHYINTR_DUP ; 
 int NGE_CFG_PHYINTR_LNK ; 
 int NGE_CFG_PHYINTR_SPD ; 
 int NGE_FILTADDR_PAR0 ; 
 int NGE_FILTADDR_PAR1 ; 
 int NGE_FILTADDR_PAR2 ; 
 int /*<<< orphan*/  NGE_FLAG_LINK ; 
 int /*<<< orphan*/  NGE_IER ; 
 int /*<<< orphan*/  NGE_IHR ; 
 int /*<<< orphan*/  NGE_IMR ; 
 int NGE_INTRS ; 
 int /*<<< orphan*/  NGE_LOCK_ASSERT (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_MIBCTL ; 
 int NGE_MIBCTL_CLEAR_CNT ; 
 int NGE_MIBCTL_FREEZE_CNT ; 
 int /*<<< orphan*/  NGE_PAUSECSR ; 
 int NGE_PAUSECSR_CNT ; 
 int NGE_PAUSECSR_PAUSE_ON_DA ; 
 int NGE_PAUSECSR_PAUSE_ON_MCAST ; 
 int NGE_PAUSECSR_RX_DATAFIFO_THR_HI ; 
 int NGE_PAUSECSR_RX_DATAFIFO_THR_LO ; 
 int NGE_PAUSECSR_RX_STATFIFO_THR_HI ; 
 int NGE_PAUSECSR_RX_STATFIFO_THR_LO ; 
 int /*<<< orphan*/  NGE_PRIOQCTL ; 
 int NGE_RXCFG ; 
 int /*<<< orphan*/  NGE_RXFILT_CTL ; 
 int /*<<< orphan*/  NGE_RXFILT_DATA ; 
 int /*<<< orphan*/  NGE_RX_CFG ; 
 int /*<<< orphan*/  NGE_RX_LISTPTR_HI ; 
 int /*<<< orphan*/  NGE_RX_LISTPTR_LO ; 
 int /*<<< orphan*/  NGE_SETBIT (struct nge_softc*,int /*<<< orphan*/ ,int) ; 
 int NGE_TXCFG ; 
 int /*<<< orphan*/  NGE_TX_CFG ; 
 int /*<<< orphan*/  NGE_TX_LISTPTR_HI ; 
 int /*<<< orphan*/  NGE_TX_LISTPTR_LO ; 
 int NGE_VIPRXCTL_IPCSUM_ENB ; 
 int NGE_VIPRXCTL_TAG_DETECT_ENB ; 
 int NGE_VIPRXCTL_TAG_STRIP_ENB ; 
 int NGE_VIPTXCTL_CSUM_PER_PKT ; 
 int NGE_VIPTXCTL_TAG_PER_PKT ; 
 int /*<<< orphan*/  NGE_VLAN_IP_RXCTL ; 
 int /*<<< orphan*/  NGE_VLAN_IP_TXCTL ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nge_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 scalar_t__ nge_list_rx_init (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_list_tx_init (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_reset (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_rxfilter (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_stop (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_tick ; 

__attribute__((used)) static void
nge_init_locked(struct nge_softc *sc)
{
	struct ifnet *ifp = sc->nge_ifp;
	struct mii_data *mii;
	uint8_t *eaddr;
	uint32_t reg;

	NGE_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	/*
	 * Cancel pending I/O and free all RX/TX buffers.
	 */
	nge_stop(sc);

	/* Reset the adapter. */
	nge_reset(sc);

	/* Disable Rx filter prior to programming Rx filter. */
	CSR_WRITE_4(sc, NGE_RXFILT_CTL, 0);
	CSR_BARRIER_4(sc, NGE_RXFILT_CTL, BUS_SPACE_BARRIER_WRITE);

	mii = device_get_softc(sc->nge_miibus);

	/* Set MAC address. */
	eaddr = IF_LLADDR(sc->nge_ifp);
	CSR_WRITE_4(sc, NGE_RXFILT_CTL, NGE_FILTADDR_PAR0);
	CSR_WRITE_4(sc, NGE_RXFILT_DATA, (eaddr[1] << 8) | eaddr[0]);
	CSR_WRITE_4(sc, NGE_RXFILT_CTL, NGE_FILTADDR_PAR1);
	CSR_WRITE_4(sc, NGE_RXFILT_DATA, (eaddr[3] << 8) | eaddr[2]);
	CSR_WRITE_4(sc, NGE_RXFILT_CTL, NGE_FILTADDR_PAR2);
	CSR_WRITE_4(sc, NGE_RXFILT_DATA, (eaddr[5] << 8) | eaddr[4]);

	/* Init circular RX list. */
	if (nge_list_rx_init(sc) == ENOBUFS) {
		device_printf(sc->nge_dev, "initialization failed: no "
			"memory for rx buffers\n");
		nge_stop(sc);
		return;
	}

	/*
	 * Init tx descriptors.
	 */
	nge_list_tx_init(sc);

	/* Set Rx filter. */
	nge_rxfilter(sc);

	/* Disable PRIQ ctl. */
	CSR_WRITE_4(sc, NGE_PRIOQCTL, 0);

	/*
	 * Set pause frames parameters.
	 *  Rx stat FIFO hi-threshold : 2 or more packets
	 *  Rx stat FIFO lo-threshold : less than 2 packets
	 *  Rx data FIFO hi-threshold : 2K or more bytes
	 *  Rx data FIFO lo-threshold : less than 2K bytes
	 *  pause time : (512ns * 0xffff) -> 33.55ms
	 */
	CSR_WRITE_4(sc, NGE_PAUSECSR,
	    NGE_PAUSECSR_PAUSE_ON_MCAST |
	    NGE_PAUSECSR_PAUSE_ON_DA |
	    ((1 << 24) & NGE_PAUSECSR_RX_STATFIFO_THR_HI) |
	    ((1 << 22) & NGE_PAUSECSR_RX_STATFIFO_THR_LO) |
	    ((1 << 20) & NGE_PAUSECSR_RX_DATAFIFO_THR_HI) |
	    ((1 << 18) & NGE_PAUSECSR_RX_DATAFIFO_THR_LO) |
	    NGE_PAUSECSR_CNT);

	/*
	 * Load the address of the RX and TX lists.
	 */
	CSR_WRITE_4(sc, NGE_RX_LISTPTR_HI,
	    NGE_ADDR_HI(sc->nge_rdata.nge_rx_ring_paddr));
	CSR_WRITE_4(sc, NGE_RX_LISTPTR_LO,
	    NGE_ADDR_LO(sc->nge_rdata.nge_rx_ring_paddr));
	CSR_WRITE_4(sc, NGE_TX_LISTPTR_HI,
	    NGE_ADDR_HI(sc->nge_rdata.nge_tx_ring_paddr));
	CSR_WRITE_4(sc, NGE_TX_LISTPTR_LO,
	    NGE_ADDR_LO(sc->nge_rdata.nge_tx_ring_paddr));

	/* Set RX configuration. */
	CSR_WRITE_4(sc, NGE_RX_CFG, NGE_RXCFG);

	CSR_WRITE_4(sc, NGE_VLAN_IP_RXCTL, 0);
	/*
	 * Enable hardware checksum validation for all IPv4
	 * packets, do not reject packets with bad checksums.
	 */
	if ((ifp->if_capenable & IFCAP_RXCSUM) != 0)
		NGE_SETBIT(sc, NGE_VLAN_IP_RXCTL, NGE_VIPRXCTL_IPCSUM_ENB);

	/*
	 * Tell the chip to detect and strip VLAN tag info from
	 * received frames. The tag will be provided in the extsts
	 * field in the RX descriptors.
	 */
	NGE_SETBIT(sc, NGE_VLAN_IP_RXCTL, NGE_VIPRXCTL_TAG_DETECT_ENB);
	if ((ifp->if_capenable & IFCAP_VLAN_HWTAGGING) != 0)
		NGE_SETBIT(sc, NGE_VLAN_IP_RXCTL, NGE_VIPRXCTL_TAG_STRIP_ENB);

	/* Set TX configuration. */
	CSR_WRITE_4(sc, NGE_TX_CFG, NGE_TXCFG);

	/*
	 * Enable TX IPv4 checksumming on a per-packet basis.
	 */
	CSR_WRITE_4(sc, NGE_VLAN_IP_TXCTL, NGE_VIPTXCTL_CSUM_PER_PKT);

	/*
	 * Tell the chip to insert VLAN tags on a per-packet basis as
	 * dictated by the code in the frame encapsulation routine.
	 */
	NGE_SETBIT(sc, NGE_VLAN_IP_TXCTL, NGE_VIPTXCTL_TAG_PER_PKT);

	/*
	 * Enable the delivery of PHY interrupts based on
	 * link/speed/duplex status changes. Also enable the
	 * extsts field in the DMA descriptors (needed for
	 * TCP/IP checksum offload on transmit).
	 */
	NGE_SETBIT(sc, NGE_CFG, NGE_CFG_PHYINTR_SPD |
	    NGE_CFG_PHYINTR_LNK | NGE_CFG_PHYINTR_DUP | NGE_CFG_EXTSTS_ENB);

	/*
	 * Configure interrupt holdoff (moderation). We can
	 * have the chip delay interrupt delivery for a certain
	 * period. Units are in 100us, and the max setting
	 * is 25500us (0xFF x 100us). Default is a 100us holdoff.
	 */
	CSR_WRITE_4(sc, NGE_IHR, sc->nge_int_holdoff);

	/*
	 * Enable MAC statistics counters and clear.
	 */
	reg = CSR_READ_4(sc, NGE_MIBCTL);
	reg &= ~NGE_MIBCTL_FREEZE_CNT;
	reg |= NGE_MIBCTL_CLEAR_CNT;
	CSR_WRITE_4(sc, NGE_MIBCTL, reg);

	/*
	 * Enable interrupts.
	 */
	CSR_WRITE_4(sc, NGE_IMR, NGE_INTRS);
#ifdef DEVICE_POLLING
	/*
	 * ... only enable interrupts if we are not polling, make sure
	 * they are off otherwise.
	 */
	if ((ifp->if_capenable & IFCAP_POLLING) != 0)
		CSR_WRITE_4(sc, NGE_IER, 0);
	else
#endif
	CSR_WRITE_4(sc, NGE_IER, 1);

	sc->nge_flags &= ~NGE_FLAG_LINK;
	mii_mediachg(mii);

	sc->nge_watchdog_timer = 0;
	callout_reset(&sc->nge_stat_ch, hz, nge_tick, sc);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
}