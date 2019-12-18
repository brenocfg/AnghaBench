#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct my_softc {int /*<<< orphan*/  my_watchdog; int /*<<< orphan*/ * my_pinfo; TYPE_2__* my_ldata; int /*<<< orphan*/  my_dev; TYPE_1__* my_info; scalar_t__ my_autoneg; struct ifnet* my_ifp; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/ * my_tx_list; int /*<<< orphan*/ * my_rx_list; } ;
struct TYPE_3__ {scalar_t__ my_did; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct my_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ENOBUFS ; 
 int IFF_BROADCAST ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 scalar_t__ MTD891ID ; 
 int /*<<< orphan*/  MY_AB ; 
 int /*<<< orphan*/  MY_BCR ; 
 int /*<<< orphan*/  MY_CLRBIT (struct my_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MY_Enhanced ; 
 int /*<<< orphan*/  MY_IMR ; 
 int MY_INTRS ; 
 int /*<<< orphan*/  MY_ISR ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int MY_PBL8 ; 
 int /*<<< orphan*/  MY_PROG ; 
 int /*<<< orphan*/  MY_PROM ; 
 int MY_RBLEN ; 
 int /*<<< orphan*/  MY_RE ; 
 int MY_RPBLE512 ; 
 int /*<<< orphan*/  MY_RXLBA ; 
 int /*<<< orphan*/  MY_SETBIT (struct my_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MY_TCRRCR ; 
 int /*<<< orphan*/  MY_TE ; 
 int MY_TFTSF ; 
 int /*<<< orphan*/  MY_TXLBA ; 
 int /*<<< orphan*/  PHY_BMCR ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct my_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 scalar_t__ my_list_rx_init (struct my_softc*) ; 
 int /*<<< orphan*/  my_list_tx_init (struct my_softc*) ; 
 int /*<<< orphan*/  my_phy_readreg (struct my_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_phy_writereg (struct my_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_reset (struct my_softc*) ; 
 int /*<<< orphan*/  my_setcfg (struct my_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_setmulti (struct my_softc*) ; 
 int /*<<< orphan*/  my_stop (struct my_softc*) ; 
 int /*<<< orphan*/  my_watchdog ; 
 int vtophys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
my_init_locked(struct my_softc *sc)
{
	struct ifnet   *ifp = sc->my_ifp;
	u_int16_t       phy_bmcr = 0;

	MY_LOCK_ASSERT(sc);
	if (sc->my_autoneg) {
		return;
	}
	if (sc->my_pinfo != NULL)
		phy_bmcr = my_phy_readreg(sc, PHY_BMCR);
	/*
	 * Cancel pending I/O and free all RX/TX buffers.
	 */
	my_stop(sc);
	my_reset(sc);

	/*
	 * Set cache alignment and burst length.
	 */
#if 0				/* 89/9/1 modify,  */
	CSR_WRITE_4(sc, MY_BCR, MY_RPBLE512);
	CSR_WRITE_4(sc, MY_TCRRCR, MY_TFTSF);
#endif
	CSR_WRITE_4(sc, MY_BCR, MY_PBL8);
	CSR_WRITE_4(sc, MY_TCRRCR, MY_TFTSF | MY_RBLEN | MY_RPBLE512);
	/*
	 * 89/12/29 add, for mtd891,
	 */
	if (sc->my_info->my_did == MTD891ID) {
		MY_SETBIT(sc, MY_BCR, MY_PROG);
		MY_SETBIT(sc, MY_TCRRCR, MY_Enhanced);
	}
	my_setcfg(sc, phy_bmcr);
	/* Init circular RX list. */
	if (my_list_rx_init(sc) == ENOBUFS) {
		device_printf(sc->my_dev, "init failed: no memory for rx buffers\n");
		my_stop(sc);
		return;
	}
	/* Init TX descriptors. */
	my_list_tx_init(sc);

	/* If we want promiscuous mode, set the allframes bit. */
	if (ifp->if_flags & IFF_PROMISC)
		MY_SETBIT(sc, MY_TCRRCR, MY_PROM);
	else
		MY_CLRBIT(sc, MY_TCRRCR, MY_PROM);

	/*
	 * Set capture broadcast bit to capture broadcast frames.
	 */
	if (ifp->if_flags & IFF_BROADCAST)
		MY_SETBIT(sc, MY_TCRRCR, MY_AB);
	else
		MY_CLRBIT(sc, MY_TCRRCR, MY_AB);

	/*
	 * Program the multicast filter, if necessary.
	 */
	my_setmulti(sc);

	/*
	 * Load the address of the RX list.
	 */
	MY_CLRBIT(sc, MY_TCRRCR, MY_RE);
	CSR_WRITE_4(sc, MY_RXLBA, vtophys(&sc->my_ldata->my_rx_list[0]));

	/*
	 * Enable interrupts.
	 */
	CSR_WRITE_4(sc, MY_IMR, MY_INTRS);
	CSR_WRITE_4(sc, MY_ISR, 0xFFFFFFFF);

	/* Enable receiver and transmitter. */
	MY_SETBIT(sc, MY_TCRRCR, MY_RE);
	MY_CLRBIT(sc, MY_TCRRCR, MY_TE);
	CSR_WRITE_4(sc, MY_TXLBA, vtophys(&sc->my_ldata->my_tx_list[0]));
	MY_SETBIT(sc, MY_TCRRCR, MY_TE);

	/* Restore state of BMCR */
	if (sc->my_pinfo != NULL)
		my_phy_writereg(sc, PHY_BMCR, phy_bmcr);
	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	callout_reset(&sc->my_watchdog, hz, my_watchdog, sc);
	return;
}