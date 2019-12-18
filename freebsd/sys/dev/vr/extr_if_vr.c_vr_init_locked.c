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
typedef  int /*<<< orphan*/  uint8_t ;
struct vr_softc {size_t vr_txthresh; int vr_quirks; scalar_t__ vr_revid; int vr_flags; int /*<<< orphan*/  vr_stat_callout; int /*<<< orphan*/  vr_dev; struct ifnet* vr_ifp; int /*<<< orphan*/  vr_miibus; } ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; int if_capenable; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_cfg; int /*<<< orphan*/  bcr_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_1 (struct vr_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct vr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int* IF_LLADDR (struct ifnet*) ; 
 scalar_t__ REV_ID_VT6102_A ; 
 scalar_t__ REV_ID_VT6105_A0 ; 
 int /*<<< orphan*/  VR_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_BCR0 ; 
 int VR_BCR0_DMA_LENGTH ; 
 int /*<<< orphan*/  VR_BCR0_DMA_STORENFWD ; 
 int /*<<< orphan*/  VR_BCR0_RXTHRESH128BYTES ; 
 int VR_BCR0_RX_THRESH ; 
 int /*<<< orphan*/  VR_BCR1 ; 
 int VR_BCR1_TX_THRESH ; 
 int VR_BCR1_VLANFILT_ENB ; 
 int /*<<< orphan*/  VR_CLRBIT (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ VR_CR0 ; 
 int VR_CR0_RX_GO ; 
 int VR_CR0_RX_ON ; 
 int VR_CR0_START ; 
 int VR_CR0_TX_ON ; 
 scalar_t__ VR_CR1 ; 
 int VR_CR1_FULLDUPLEX ; 
 int VR_CR1_TX_NOPOLL ; 
 scalar_t__ VR_FLOWCR0 ; 
 scalar_t__ VR_FLOWCR1 ; 
 int VR_FLOWCR1_TXHI24 ; 
 int VR_FLOWCR1_TXLO8 ; 
 int VR_FLOWCR1_XONXOFF ; 
 int VR_F_LINK ; 
 int VR_F_TXPAUSE ; 
 int /*<<< orphan*/  VR_IMR ; 
 int VR_INTRS ; 
 int /*<<< orphan*/  VR_ISR ; 
 int /*<<< orphan*/  VR_LOCK_ASSERT (struct vr_softc*) ; 
 int /*<<< orphan*/  VR_MCAST_CAM ; 
 int /*<<< orphan*/  VR_MII_IMR ; 
 scalar_t__ VR_PAR0 ; 
 int /*<<< orphan*/  VR_PAUSETIMER ; 
 int VR_Q_CAM ; 
 int /*<<< orphan*/  VR_RXADDR ; 
 int /*<<< orphan*/  VR_RXCFG ; 
 int VR_RXCFG_RX_THRESH ; 
 int /*<<< orphan*/  VR_RXTHRESH_128BYTES ; 
 int /*<<< orphan*/  VR_RX_RING_ADDR (struct vr_softc*,int /*<<< orphan*/ ) ; 
 int VR_RX_RING_CNT ; 
 int /*<<< orphan*/  VR_SETBIT (struct vr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_TXADDR ; 
 int /*<<< orphan*/  VR_TXCFG ; 
 int VR_TXCFG_RXTAGCTL ; 
 int VR_TXCFG_TXTAGEN ; 
 int VR_TXCFG_TX_THRESH ; 
 int /*<<< orphan*/  VR_TX_RING_ADDR (struct vr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_VLAN_CAM ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vr_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 int /*<<< orphan*/  vr_cam_data (struct vr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vr_cam_mask (struct vr_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vr_reset (struct vr_softc*) ; 
 scalar_t__ vr_rx_ring_init (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_set_filter (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_stop (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_tick ; 
 int /*<<< orphan*/  vr_tx_ring_init (struct vr_softc*) ; 
 TYPE_1__* vr_tx_threshold_tables ; 

__attribute__((used)) static void
vr_init_locked(struct vr_softc *sc)
{
	struct ifnet		*ifp;
	struct mii_data		*mii;
	bus_addr_t		addr;
	int			i;

	VR_LOCK_ASSERT(sc);

	ifp = sc->vr_ifp;
	mii = device_get_softc(sc->vr_miibus);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	/* Cancel pending I/O and free all RX/TX buffers. */
	vr_stop(sc);
	vr_reset(sc);

	/* Set our station address. */
	for (i = 0; i < ETHER_ADDR_LEN; i++)
		CSR_WRITE_1(sc, VR_PAR0 + i, IF_LLADDR(sc->vr_ifp)[i]);

	/* Set DMA size. */
	VR_CLRBIT(sc, VR_BCR0, VR_BCR0_DMA_LENGTH);
	VR_SETBIT(sc, VR_BCR0, VR_BCR0_DMA_STORENFWD);

	/*
	 * BCR0 and BCR1 can override the RXCFG and TXCFG registers,
	 * so we must set both.
	 */
	VR_CLRBIT(sc, VR_BCR0, VR_BCR0_RX_THRESH);
	VR_SETBIT(sc, VR_BCR0, VR_BCR0_RXTHRESH128BYTES);

	VR_CLRBIT(sc, VR_BCR1, VR_BCR1_TX_THRESH);
	VR_SETBIT(sc, VR_BCR1, vr_tx_threshold_tables[sc->vr_txthresh].bcr_cfg);

	VR_CLRBIT(sc, VR_RXCFG, VR_RXCFG_RX_THRESH);
	VR_SETBIT(sc, VR_RXCFG, VR_RXTHRESH_128BYTES);

	VR_CLRBIT(sc, VR_TXCFG, VR_TXCFG_TX_THRESH);
	VR_SETBIT(sc, VR_TXCFG, vr_tx_threshold_tables[sc->vr_txthresh].tx_cfg);

	/* Init circular RX list. */
	if (vr_rx_ring_init(sc) != 0) {
		device_printf(sc->vr_dev,
		    "initialization failed: no memory for rx buffers\n");
		vr_stop(sc);
		return;
	}

	/* Init tx descriptors. */
	vr_tx_ring_init(sc);

	if ((sc->vr_quirks & VR_Q_CAM) != 0) {
		uint8_t vcam[2] = { 0, 0 };

		/* Disable VLAN hardware tag insertion/stripping. */
		VR_CLRBIT(sc, VR_TXCFG, VR_TXCFG_TXTAGEN | VR_TXCFG_RXTAGCTL);
		/* Disable VLAN hardware filtering. */
		VR_CLRBIT(sc, VR_BCR1, VR_BCR1_VLANFILT_ENB);
		/* Disable all CAM entries. */
		vr_cam_mask(sc, VR_MCAST_CAM, 0);
		vr_cam_mask(sc, VR_VLAN_CAM, 0);
		/* Enable the first VLAN CAM. */
		vr_cam_data(sc, VR_VLAN_CAM, 0, vcam);
		vr_cam_mask(sc, VR_VLAN_CAM, 1);
	}

	/*
	 * Set up receive filter.
	 */
	vr_set_filter(sc);

	/*
	 * Load the address of the RX ring.
	 */
	addr = VR_RX_RING_ADDR(sc, 0);
	CSR_WRITE_4(sc, VR_RXADDR, VR_ADDR_LO(addr));
	/*
	 * Load the address of the TX ring.
	 */
	addr = VR_TX_RING_ADDR(sc, 0);
	CSR_WRITE_4(sc, VR_TXADDR, VR_ADDR_LO(addr));
	/* Default : full-duplex, no Tx poll. */
	CSR_WRITE_1(sc, VR_CR1, VR_CR1_FULLDUPLEX | VR_CR1_TX_NOPOLL);

	/* Set flow-control parameters for Rhine III. */
	if (sc->vr_revid >= REV_ID_VT6105_A0) {
		/*
		 * Configure Rx buffer count available for incoming
		 * packet.
		 * Even though data sheet says almost nothing about
		 * this register, this register should be updated
		 * whenever driver adds new RX buffers to controller.
		 * Otherwise, XON frame is not sent to link partner
		 * even if controller has enough RX buffers and you
		 * would be isolated from network.
		 * The controller is not smart enough to know number
		 * of available RX buffers so driver have to let
		 * controller know how many RX buffers are posted.
		 * In other words, this register works like a residue
		 * counter for RX buffers and should be initialized
		 * to the number of total RX buffers  - 1 before
		 * enabling RX MAC.  Note, this register is 8bits so
		 * it effectively limits the maximum number of RX
		 * buffer to be configured by controller is 255.
		 */
		CSR_WRITE_1(sc, VR_FLOWCR0, VR_RX_RING_CNT - 1);
		/*
		 * Tx pause low threshold : 8 free receive buffers
		 * Tx pause XON high threshold : 24 free receive buffers
		 */
		CSR_WRITE_1(sc, VR_FLOWCR1,
		    VR_FLOWCR1_TXLO8 | VR_FLOWCR1_TXHI24 | VR_FLOWCR1_XONXOFF);
		/* Set Tx pause timer. */
		CSR_WRITE_2(sc, VR_PAUSETIMER, 0xffff);
	}

	/* Enable receiver and transmitter. */
	CSR_WRITE_1(sc, VR_CR0,
	    VR_CR0_START | VR_CR0_TX_ON | VR_CR0_RX_ON | VR_CR0_RX_GO);

	CSR_WRITE_2(sc, VR_ISR, 0xFFFF);
#ifdef DEVICE_POLLING
	/*
	 * Disable interrupts if we are polling.
	 */
	if (ifp->if_capenable & IFCAP_POLLING)
		CSR_WRITE_2(sc, VR_IMR, 0);
	else
#endif
	/*
	 * Enable interrupts and disable MII intrs.
	 */
	CSR_WRITE_2(sc, VR_IMR, VR_INTRS);
	if (sc->vr_revid > REV_ID_VT6102_A)
		CSR_WRITE_2(sc, VR_MII_IMR, 0);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	sc->vr_flags &= ~(VR_F_LINK | VR_F_TXPAUSE);
	mii_mediachg(mii);

	callout_reset(&sc->vr_stat_callout, hz, vr_tick, sc);
}