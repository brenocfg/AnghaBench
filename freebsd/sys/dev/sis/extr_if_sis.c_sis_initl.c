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
typedef  int uint8_t ;
struct sis_softc {scalar_t__ sis_type; scalar_t__ sis_srr; scalar_t__ sis_manual_pad; int /*<<< orphan*/  sis_stat_ch; int /*<<< orphan*/  sis_flags; int /*<<< orphan*/  sis_tx_paddr; int /*<<< orphan*/  sis_rx_paddr; int /*<<< orphan*/  sis_dev; struct ifnet* sis_ifp; int /*<<< orphan*/  sis_miibus; } ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; int if_capenable; } ;

/* Variables and functions */
 int CSR_READ_4 (struct sis_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int* IF_LLADDR (struct ifnet*) ; 
 int NS_FILTADDR_PAR0 ; 
 int NS_FILTADDR_PAR1 ; 
 int NS_FILTADDR_PAR2 ; 
 int /*<<< orphan*/  NS_IHR ; 
 int /*<<< orphan*/  NS_PHY_CR ; 
 int /*<<< orphan*/  NS_PHY_DSPCFG ; 
 int /*<<< orphan*/  NS_PHY_PAGE ; 
 int /*<<< orphan*/  NS_PHY_SDCFG ; 
 int /*<<< orphan*/  NS_PHY_TDATA ; 
 scalar_t__ NS_SRR_15D ; 
 scalar_t__ NS_SRR_16A ; 
 int SIS_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIS_CFG ; 
 int SIS_CFG_EDB_MASTER_EN ; 
 int /*<<< orphan*/  SIS_CLRBIT (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIS_CSR ; 
 int SIS_CSR_RX_DISABLE ; 
 int SIS_CSR_TX_DISABLE ; 
 int SIS_FILTADDR_PAR0 ; 
 int SIS_FILTADDR_PAR1 ; 
 int SIS_FILTADDR_PAR2 ; 
 int /*<<< orphan*/  SIS_FLAG_LINK ; 
 int /*<<< orphan*/  SIS_FLAG_MANUAL_PAD ; 
 int /*<<< orphan*/  SIS_IER ; 
 int /*<<< orphan*/  SIS_IMR ; 
 int SIS_INTRS ; 
 int /*<<< orphan*/  SIS_LOCK_ASSERT (struct sis_softc*) ; 
 int SIS_RXCFG256 ; 
 int SIS_RXCFG64 ; 
 int /*<<< orphan*/  SIS_RXCFG_RX_JABBER ; 
 int /*<<< orphan*/  SIS_RXFILT_CTL ; 
 int /*<<< orphan*/  SIS_RXFILT_DATA ; 
 int /*<<< orphan*/  SIS_RX_CFG ; 
 int /*<<< orphan*/  SIS_RX_LISTPTR ; 
 int /*<<< orphan*/  SIS_SETBIT (struct sis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SIS_TXCFG_100 ; 
 int /*<<< orphan*/  SIS_TX_CFG ; 
 int /*<<< orphan*/  SIS_TX_LISTPTR ; 
 scalar_t__ SIS_TYPE_83815 ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sis_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 int /*<<< orphan*/  sis_reset (struct sis_softc*) ; 
 scalar_t__ sis_ring_init (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_rxfilter (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_stop (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_tick ; 

__attribute__((used)) static void
sis_initl(struct sis_softc *sc)
{
	struct ifnet		*ifp = sc->sis_ifp;
	struct mii_data		*mii;
	uint8_t			*eaddr;

	SIS_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	/*
	 * Cancel pending I/O and free all RX/TX buffers.
	 */
	sis_stop(sc);
	/*
	 * Reset the chip to a known state.
	 */
	sis_reset(sc);
#ifdef notyet
	if (sc->sis_type == SIS_TYPE_83815 && sc->sis_srr >= NS_SRR_16A) {
		/*
		 * Configure 400usec of interrupt holdoff.  This is based
		 * on emperical tests on a Soekris 4801.
 		 */
		CSR_WRITE_4(sc, NS_IHR, 0x100 | 4);
	}
#endif

	mii = device_get_softc(sc->sis_miibus);

	/* Set MAC address */
	eaddr = IF_LLADDR(sc->sis_ifp);
	if (sc->sis_type == SIS_TYPE_83815) {
		CSR_WRITE_4(sc, SIS_RXFILT_CTL, NS_FILTADDR_PAR0);
		CSR_WRITE_4(sc, SIS_RXFILT_DATA, eaddr[0] | eaddr[1] << 8);
		CSR_WRITE_4(sc, SIS_RXFILT_CTL, NS_FILTADDR_PAR1);
		CSR_WRITE_4(sc, SIS_RXFILT_DATA, eaddr[2] | eaddr[3] << 8);
		CSR_WRITE_4(sc, SIS_RXFILT_CTL, NS_FILTADDR_PAR2);
		CSR_WRITE_4(sc, SIS_RXFILT_DATA, eaddr[4] | eaddr[5] << 8);
	} else {
		CSR_WRITE_4(sc, SIS_RXFILT_CTL, SIS_FILTADDR_PAR0);
		CSR_WRITE_4(sc, SIS_RXFILT_DATA, eaddr[0] | eaddr[1] << 8);
		CSR_WRITE_4(sc, SIS_RXFILT_CTL, SIS_FILTADDR_PAR1);
		CSR_WRITE_4(sc, SIS_RXFILT_DATA, eaddr[2] | eaddr[3] << 8);
		CSR_WRITE_4(sc, SIS_RXFILT_CTL, SIS_FILTADDR_PAR2);
		CSR_WRITE_4(sc, SIS_RXFILT_DATA, eaddr[4] | eaddr[5] << 8);
	}

	/* Init circular TX/RX lists. */
	if (sis_ring_init(sc) != 0) {
		device_printf(sc->sis_dev,
		    "initialization failed: no memory for rx buffers\n");
		sis_stop(sc);
		return;
	}

	if (sc->sis_type == SIS_TYPE_83815) {
		if (sc->sis_manual_pad != 0)
			sc->sis_flags |= SIS_FLAG_MANUAL_PAD;
		else
			sc->sis_flags &= ~SIS_FLAG_MANUAL_PAD;
	}

	/*
	 * Short Cable Receive Errors (MP21.E)
	 * also: Page 78 of the DP83815 data sheet (september 2002 version)
	 * recommends the following register settings "for optimum
	 * performance." for rev 15C.  Set this also for 15D parts as
	 * they require it in practice.
	 */
	if (sc->sis_type == SIS_TYPE_83815 && sc->sis_srr <= NS_SRR_15D) {
		CSR_WRITE_4(sc, NS_PHY_PAGE, 0x0001);
		CSR_WRITE_4(sc, NS_PHY_CR, 0x189C);
		/* set val for c2 */
		CSR_WRITE_4(sc, NS_PHY_TDATA, 0x0000);
		/* load/kill c2 */
		CSR_WRITE_4(sc, NS_PHY_DSPCFG, 0x5040);
		/* rais SD off, from 4 to c */
		CSR_WRITE_4(sc, NS_PHY_SDCFG, 0x008C);
		CSR_WRITE_4(sc, NS_PHY_PAGE, 0);
	}

	sis_rxfilter(sc);

	/*
	 * Load the address of the RX and TX lists.
	 */
	CSR_WRITE_4(sc, SIS_RX_LISTPTR, SIS_ADDR_LO(sc->sis_rx_paddr));
	CSR_WRITE_4(sc, SIS_TX_LISTPTR, SIS_ADDR_LO(sc->sis_tx_paddr));

	/* SIS_CFG_EDB_MASTER_EN indicates the EDB bus is used instead of
	 * the PCI bus. When this bit is set, the Max DMA Burst Size
	 * for TX/RX DMA should be no larger than 16 double words.
	 */
	if (CSR_READ_4(sc, SIS_CFG) & SIS_CFG_EDB_MASTER_EN) {
		CSR_WRITE_4(sc, SIS_RX_CFG, SIS_RXCFG64);
	} else {
		CSR_WRITE_4(sc, SIS_RX_CFG, SIS_RXCFG256);
	}

	/* Accept Long Packets for VLAN support */
	SIS_SETBIT(sc, SIS_RX_CFG, SIS_RXCFG_RX_JABBER);

	/*
	 * Assume 100Mbps link, actual MAC configuration is done
	 * after getting a valid link.
	 */
	CSR_WRITE_4(sc, SIS_TX_CFG, SIS_TXCFG_100);

	/*
	 * Enable interrupts.
	 */
	CSR_WRITE_4(sc, SIS_IMR, SIS_INTRS);
#ifdef DEVICE_POLLING
	/*
	 * ... only enable interrupts if we are not polling, make sure
	 * they are off otherwise.
	 */
	if (ifp->if_capenable & IFCAP_POLLING)
		CSR_WRITE_4(sc, SIS_IER, 0);
	else
#endif
	CSR_WRITE_4(sc, SIS_IER, 1);

	/* Clear MAC disable. */
	SIS_CLRBIT(sc, SIS_CSR, SIS_CSR_TX_DISABLE | SIS_CSR_RX_DISABLE);

	sc->sis_flags &= ~SIS_FLAG_LINK;
	mii_mediachg(mii);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	callout_reset(&sc->sis_stat_ch, hz,  sis_tick, sc);
}