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
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  sge_rx_paddr; int /*<<< orphan*/  sge_tx_paddr; } ;
struct sge_softc {int sge_flags; int sge_intrcontrol; int sge_intrtimer; int /*<<< orphan*/  sge_stat_ch; TYPE_1__ sge_ldata; int /*<<< orphan*/  sge_dev; int /*<<< orphan*/  sge_miibus; struct ifnet* sge_ifp; } ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_1 (struct sge_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct sge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sge_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ENOBUFS ; 
 int ETHER_ADDR_LEN ; 
 int ETHER_MAX_LEN ; 
 int ETHER_VLAN_ENCAP_LEN ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/ * IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  IntrControl ; 
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  IntrStatus ; 
 int /*<<< orphan*/  IntrTimer ; 
 int RXMAC_CSUM_ENB ; 
 int RXMAC_PAD_ENB ; 
 int RXMAC_STRIP_FCS ; 
 int /*<<< orphan*/  RX_CTL ; 
 int RX_CTL_ENB ; 
 int RX_CTL_POLL ; 
 int /*<<< orphan*/  RX_DESC ; 
 int /*<<< orphan*/  RxMPSControl ; 
 scalar_t__ RxMacAddr ; 
 int /*<<< orphan*/  RxMacControl ; 
 int /*<<< orphan*/  RxWakeOnLan ; 
 int /*<<< orphan*/  RxWakeOnLanData ; 
 int SGE_ADDR_LO (int /*<<< orphan*/ ) ; 
 int SGE_FLAG_FASTETHER ; 
 int SGE_FLAG_FDX ; 
 int SGE_FLAG_LINK ; 
 int SGE_FLAG_RGMII ; 
 int SGE_FLAG_SPEED_1000 ; 
 int SGE_INTRS ; 
 int /*<<< orphan*/  SGE_LOCK_ASSERT (struct sge_softc*) ; 
 int SGE_RX_PAD_BYTES ; 
 int /*<<< orphan*/  StationControl ; 
 int /*<<< orphan*/  TX_CTL ; 
 int TX_CTL_ENB ; 
 int /*<<< orphan*/  TX_DESC ; 
 int /*<<< orphan*/  TxMacControl ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sge_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 scalar_t__ sge_list_rx_init (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_list_tx_init (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_reset (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_rxfilter (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_setvlan (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_stop (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_tick ; 

__attribute__((used)) static void
sge_init_locked(struct sge_softc *sc)
{
	struct ifnet *ifp;
	struct mii_data *mii;
	uint16_t rxfilt;
	int i;

	SGE_LOCK_ASSERT(sc);
	ifp = sc->sge_ifp;
	mii = device_get_softc(sc->sge_miibus);
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;
	/*
	 * Cancel pending I/O and free all RX/TX buffers.
	 */
	sge_stop(sc);
	sge_reset(sc);

	/* Init circular RX list. */
	if (sge_list_rx_init(sc) == ENOBUFS) {
		device_printf(sc->sge_dev, "no memory for Rx buffers\n");
		sge_stop(sc);
		return;
	}
	/* Init TX descriptors. */
	sge_list_tx_init(sc);
	/*
	 * Load the address of the RX and TX lists.
	 */
	CSR_WRITE_4(sc, TX_DESC, SGE_ADDR_LO(sc->sge_ldata.sge_tx_paddr));
	CSR_WRITE_4(sc, RX_DESC, SGE_ADDR_LO(sc->sge_ldata.sge_rx_paddr));

	CSR_WRITE_4(sc, TxMacControl, 0x60);
	CSR_WRITE_4(sc, RxWakeOnLan, 0);
	CSR_WRITE_4(sc, RxWakeOnLanData, 0);
	/* Allow receiving VLAN frames. */
	CSR_WRITE_2(sc, RxMPSControl, ETHER_MAX_LEN + ETHER_VLAN_ENCAP_LEN +
	    SGE_RX_PAD_BYTES);

	for (i = 0; i < ETHER_ADDR_LEN; i++)
		CSR_WRITE_1(sc, RxMacAddr + i, IF_LLADDR(ifp)[i]);
	/* Configure RX MAC. */
	rxfilt = RXMAC_STRIP_FCS | RXMAC_PAD_ENB | RXMAC_CSUM_ENB;
	CSR_WRITE_2(sc, RxMacControl, rxfilt);
	sge_rxfilter(sc);
	sge_setvlan(sc);

	/* Initialize default speed/duplex information. */
	if ((sc->sge_flags & SGE_FLAG_FASTETHER) == 0)
		sc->sge_flags |= SGE_FLAG_SPEED_1000;
	sc->sge_flags |= SGE_FLAG_FDX;
	if ((sc->sge_flags & SGE_FLAG_RGMII) != 0)
		CSR_WRITE_4(sc, StationControl, 0x04008001);
	else
		CSR_WRITE_4(sc, StationControl, 0x04000001);
	/*
	 * XXX Try to mitigate interrupts.
	 */
	CSR_WRITE_4(sc, IntrControl, 0x08880000);
#ifdef notyet
	if (sc->sge_intrcontrol != 0)
		CSR_WRITE_4(sc, IntrControl, sc->sge_intrcontrol);
	if (sc->sge_intrtimer != 0)
		CSR_WRITE_4(sc, IntrTimer, sc->sge_intrtimer);
#endif

	/*
	 * Clear and enable interrupts.
	 */
	CSR_WRITE_4(sc, IntrStatus, 0xFFFFFFFF);
	CSR_WRITE_4(sc, IntrMask, SGE_INTRS);

	/* Enable receiver and transmitter. */
	CSR_WRITE_4(sc, TX_CTL, 0x1a00 | TX_CTL_ENB);
	CSR_WRITE_4(sc, RX_CTL, 0x1a00 | 0x000c | RX_CTL_POLL | RX_CTL_ENB);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	sc->sge_flags &= ~SGE_FLAG_LINK;
	mii_mediachg(mii);
	callout_reset(&sc->sge_stat_ch, hz, sge_tick, sc);
}