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
struct ifmedia {int /*<<< orphan*/  ifm_media; } ;
struct mii_data {struct ifmedia mii_media; } ;
struct ifnet {int if_drv_flags; int if_capenable; } ;
struct dc_softc {int dc_flags; int dc_cachesize; scalar_t__ dc_txthresh; scalar_t__ dc_type; int dc_link; int /*<<< orphan*/  dc_wdog_ch; scalar_t__ dc_wdog_timer; int /*<<< orphan*/  dc_stat_ch; int /*<<< orphan*/  dc_dev; int /*<<< orphan*/  dc_miibus; struct ifnet* dc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_4 (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int DC_21143_NWAY ; 
 int DC_BURSTLEN_16LONG ; 
 int DC_BURSTLEN_USECA ; 
 int /*<<< orphan*/  DC_BUSCTL ; 
 int DC_BUSCTL_ARBITRATION ; 
 int DC_BUSCTL_MRLE ; 
 int DC_BUSCTL_MRME ; 
 int DC_CACHEALIGN_16LONG ; 
 int DC_CACHEALIGN_32LONG ; 
 int DC_CACHEALIGN_8LONG ; 
 int DC_CACHEALIGN_NONE ; 
 int /*<<< orphan*/  DC_CLRBIT (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_FRAMESDISCARDED ; 
 int /*<<< orphan*/  DC_IMR ; 
 int DC_INTRS ; 
 int /*<<< orphan*/  DC_ISR ; 
 scalar_t__ DC_IS_ASIX (struct dc_softc*) ; 
 scalar_t__ DC_IS_DAVICOM (struct dc_softc*) ; 
 scalar_t__ DC_IS_INTEL (struct dc_softc*) ; 
 scalar_t__ DC_IS_MACRONIX (struct dc_softc*) ; 
 scalar_t__ DC_IS_PNICII (struct dc_softc*) ; 
 scalar_t__ DC_IS_ULI (struct dc_softc*) ; 
 scalar_t__ DC_IS_XIRCOM (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_LOCK_ASSERT (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_MX_MAGICPACKET ; 
 int DC_MX_MAGIC_98713 ; 
 int DC_MX_MAGIC_98715 ; 
 int /*<<< orphan*/  DC_NETCFG ; 
 int DC_NETCFG_NO_RXCRC ; 
 int DC_NETCFG_RX_ON ; 
 int DC_NETCFG_STORENFWD ; 
 int DC_NETCFG_TX_BACKOFF ; 
 int DC_NETCFG_TX_ON ; 
 int DC_NETCFG_TX_THRESH ; 
 int /*<<< orphan*/  DC_RXADDR ; 
 int DC_RXDESC (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_RXSTART ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_SIAGP ; 
 int DC_SIAGP_INT1_EN ; 
 int DC_SIAGP_MD_GP0_OUTPUT ; 
 int DC_SIAGP_MD_GP2_OUTPUT ; 
 int DC_SIAGP_WRITE_EN ; 
 int DC_TULIP_LEDS ; 
 int /*<<< orphan*/  DC_TXADDR ; 
 int DC_TXDESC (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int DC_TXPOLL_1 ; 
 scalar_t__ DC_TXTHRESH_MAX ; 
 int DC_TXTHRESH_MIN ; 
 int DC_TX_POLL ; 
 int DC_TX_STORENFWD ; 
 scalar_t__ DC_TYPE_98713 ; 
 int /*<<< orphan*/  DC_WATCHDOG ; 
 int DC_WDOG_ACTIVITY ; 
 int DC_WDOG_CTLWREN ; 
 int DC_WDOG_HOSTUNJAB ; 
 int DC_WDOG_JABBERCLK ; 
 int DC_WDOG_LINK ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ ENOBUFS ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ IFM_HPNA_1 ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct dc_softc*) ; 
 int /*<<< orphan*/  dc_apply_fixup (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_ifmedia_upd_locked (struct dc_softc*) ; 
 scalar_t__ dc_list_rx_init (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_list_tx_init (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_reset (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_setfilt (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_stop (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_tick ; 
 int /*<<< orphan*/  dc_watchdog ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 

__attribute__((used)) static void
dc_init_locked(struct dc_softc *sc)
{
	struct ifnet *ifp = sc->dc_ifp;
	struct mii_data *mii;
	struct ifmedia *ifm;

	DC_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	mii = device_get_softc(sc->dc_miibus);

	/*
	 * Cancel pending I/O and free all RX/TX buffers.
	 */
	dc_stop(sc);
	dc_reset(sc);
	if (DC_IS_INTEL(sc)) {
		ifm = &mii->mii_media;
		dc_apply_fixup(sc, ifm->ifm_media);
	}

	/*
	 * Set cache alignment and burst length.
	 */
	if (DC_IS_ASIX(sc) || DC_IS_DAVICOM(sc) || DC_IS_ULI(sc))
		CSR_WRITE_4(sc, DC_BUSCTL, 0);
	else
		CSR_WRITE_4(sc, DC_BUSCTL, DC_BUSCTL_MRME | DC_BUSCTL_MRLE);
	/*
	 * Evenly share the bus between receive and transmit process.
	 */
	if (DC_IS_INTEL(sc))
		DC_SETBIT(sc, DC_BUSCTL, DC_BUSCTL_ARBITRATION);
	if (DC_IS_DAVICOM(sc) || DC_IS_INTEL(sc)) {
		DC_SETBIT(sc, DC_BUSCTL, DC_BURSTLEN_USECA);
	} else {
		DC_SETBIT(sc, DC_BUSCTL, DC_BURSTLEN_16LONG);
	}
	if (sc->dc_flags & DC_TX_POLL)
		DC_SETBIT(sc, DC_BUSCTL, DC_TXPOLL_1);
	switch(sc->dc_cachesize) {
	case 32:
		DC_SETBIT(sc, DC_BUSCTL, DC_CACHEALIGN_32LONG);
		break;
	case 16:
		DC_SETBIT(sc, DC_BUSCTL, DC_CACHEALIGN_16LONG);
		break;
	case 8:
		DC_SETBIT(sc, DC_BUSCTL, DC_CACHEALIGN_8LONG);
		break;
	case 0:
	default:
		DC_SETBIT(sc, DC_BUSCTL, DC_CACHEALIGN_NONE);
		break;
	}

	if (sc->dc_flags & DC_TX_STORENFWD)
		DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_STORENFWD);
	else {
		if (sc->dc_txthresh > DC_TXTHRESH_MAX) {
			DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_STORENFWD);
		} else {
			DC_CLRBIT(sc, DC_NETCFG, DC_NETCFG_STORENFWD);
			DC_SETBIT(sc, DC_NETCFG, sc->dc_txthresh);
		}
	}

	DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_NO_RXCRC);
	DC_CLRBIT(sc, DC_NETCFG, DC_NETCFG_TX_BACKOFF);

	if (DC_IS_MACRONIX(sc) || DC_IS_PNICII(sc)) {
		/*
		 * The app notes for the 98713 and 98715A say that
		 * in order to have the chips operate properly, a magic
		 * number must be written to CSR16. Macronix does not
		 * document the meaning of these bits so there's no way
		 * to know exactly what they do. The 98713 has a magic
		 * number all its own; the rest all use a different one.
		 */
		DC_CLRBIT(sc, DC_MX_MAGICPACKET, 0xFFFF0000);
		if (sc->dc_type == DC_TYPE_98713)
			DC_SETBIT(sc, DC_MX_MAGICPACKET, DC_MX_MAGIC_98713);
		else
			DC_SETBIT(sc, DC_MX_MAGICPACKET, DC_MX_MAGIC_98715);
	}

	if (DC_IS_XIRCOM(sc)) {
		/*
		 * setup General Purpose Port mode and data so the tulip
		 * can talk to the MII.
		 */
		CSR_WRITE_4(sc, DC_SIAGP, DC_SIAGP_WRITE_EN | DC_SIAGP_INT1_EN |
			   DC_SIAGP_MD_GP2_OUTPUT | DC_SIAGP_MD_GP0_OUTPUT);
		DELAY(10);
		CSR_WRITE_4(sc, DC_SIAGP, DC_SIAGP_INT1_EN |
			   DC_SIAGP_MD_GP2_OUTPUT | DC_SIAGP_MD_GP0_OUTPUT);
		DELAY(10);
	}

	DC_CLRBIT(sc, DC_NETCFG, DC_NETCFG_TX_THRESH);
	DC_SETBIT(sc, DC_NETCFG, DC_TXTHRESH_MIN);

	/* Init circular RX list. */
	if (dc_list_rx_init(sc) == ENOBUFS) {
		device_printf(sc->dc_dev,
		    "initialization failed: no memory for rx buffers\n");
		dc_stop(sc);
		return;
	}

	/*
	 * Init TX descriptors.
	 */
	dc_list_tx_init(sc);

	/*
	 * Load the address of the RX list.
	 */
	CSR_WRITE_4(sc, DC_RXADDR, DC_RXDESC(sc, 0));
	CSR_WRITE_4(sc, DC_TXADDR, DC_TXDESC(sc, 0));

	/*
	 * Enable interrupts.
	 */
#ifdef DEVICE_POLLING
	/*
	 * ... but only if we are not polling, and make sure they are off in
	 * the case of polling. Some cards (e.g. fxp) turn interrupts on
	 * after a reset.
	 */
	if (ifp->if_capenable & IFCAP_POLLING)
		CSR_WRITE_4(sc, DC_IMR, 0x00000000);
	else
#endif
	CSR_WRITE_4(sc, DC_IMR, DC_INTRS);
	CSR_WRITE_4(sc, DC_ISR, 0xFFFFFFFF);

	/* Initialize TX jabber and RX watchdog timer. */
	if (DC_IS_ULI(sc))
		CSR_WRITE_4(sc, DC_WATCHDOG, DC_WDOG_JABBERCLK |
		    DC_WDOG_HOSTUNJAB);

	/* Enable transmitter. */
	DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_TX_ON);

	/*
	 * If this is an Intel 21143 and we're not using the
	 * MII port, program the LED control pins so we get
	 * link and activity indications.
	 */
	if (sc->dc_flags & DC_TULIP_LEDS) {
		CSR_WRITE_4(sc, DC_WATCHDOG,
		    DC_WDOG_CTLWREN | DC_WDOG_LINK | DC_WDOG_ACTIVITY);
		CSR_WRITE_4(sc, DC_WATCHDOG, 0);
	}

	/*
	 * Load the RX/multicast filter. We do this sort of late
	 * because the filter programming scheme on the 21143 and
	 * some clones requires DMAing a setup frame via the TX
	 * engine, and we need the transmitter enabled for that.
	 */
	dc_setfilt(sc);

	/* Enable receiver. */
	DC_SETBIT(sc, DC_NETCFG, DC_NETCFG_RX_ON);
	CSR_WRITE_4(sc, DC_RXSTART, 0xFFFFFFFF);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	dc_ifmedia_upd_locked(sc);

	/* Clear missed frames and overflow counter. */
	CSR_READ_4(sc, DC_FRAMESDISCARDED);

	/* Don't start the ticker if this is a homePNA link. */
	if (IFM_SUBTYPE(mii->mii_media.ifm_media) == IFM_HPNA_1)
		sc->dc_link = 1;
	else {
		if (sc->dc_flags & DC_21143_NWAY)
			callout_reset(&sc->dc_stat_ch, hz/10, dc_tick, sc);
		else
			callout_reset(&sc->dc_stat_ch, hz, dc_tick, sc);
	}

	sc->dc_wdog_timer = 0;
	callout_reset(&sc->dc_wdog_ch, hz, dc_watchdog, sc);
}