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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ rl_rx_buf_paddr; } ;
struct rl_softc {int /*<<< orphan*/  rl_stat_callout; int /*<<< orphan*/  rl_cfg1; int /*<<< orphan*/  rl_flags; int /*<<< orphan*/  rl_txthresh; TYPE_1__ rl_cdata; struct ifnet* rl_ifp; int /*<<< orphan*/  rl_twister; scalar_t__ rl_twister_enable; int /*<<< orphan*/  rl_miibus; } ;
struct mii_data {int dummy; } ;
struct ifnet {int if_drv_flags; int if_capenable; } ;
typedef  int /*<<< orphan*/  eaddr ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_LINK ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct rl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct rl_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CSR_WRITE_STREAM_4 (struct rl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int RL_CFG1_DRVLOAD ; 
 int RL_CFG1_FULLDUPLEX ; 
 int RL_CMD_RX_ENB ; 
 int RL_CMD_TX_ENB ; 
 int /*<<< orphan*/  RL_COMMAND ; 
 int /*<<< orphan*/  RL_EECMD ; 
 int RL_EEMODE_OFF ; 
 int RL_EEMODE_WRITECFG ; 
 int /*<<< orphan*/  RL_FLAG_LINK ; 
 int /*<<< orphan*/  RL_IDR0 ; 
 int /*<<< orphan*/  RL_IDR4 ; 
 int /*<<< orphan*/  RL_IMR ; 
 int /*<<< orphan*/  RL_INTRS ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_MISSEDPKT ; 
 int /*<<< orphan*/  RL_RXADDR ; 
 int /*<<< orphan*/  RL_RXCFG ; 
 scalar_t__ RL_RXCFG_CONFIG ; 
 scalar_t__ RL_RX_8139_BUF_RESERVE ; 
 int /*<<< orphan*/  RL_TXCFG ; 
 scalar_t__ RL_TXCFG_CONFIG ; 
 int /*<<< orphan*/  RL_TX_THRESH_INIT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rl_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 int /*<<< orphan*/  rl_list_rx_init (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_list_tx_init (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_reset (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_rxfilter (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_stop (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_tick ; 

__attribute__((used)) static void
rl_init_locked(struct rl_softc *sc)
{
	struct ifnet		*ifp = sc->rl_ifp;
	struct mii_data		*mii;
	uint32_t		eaddr[2];

	RL_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->rl_miibus);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	/*
	 * Cancel pending I/O and free all RX/TX buffers.
	 */
	rl_stop(sc);

	rl_reset(sc);
	if (sc->rl_twister_enable) {
		/*
		 * Reset twister register tuning state.  The twister
		 * registers and their tuning are undocumented, but
		 * are necessary to cope with bad links.  rl_twister =
		 * DONE here will disable this entirely.
		 */
		sc->rl_twister = CHK_LINK;
	}

	/*
	 * Init our MAC address.  Even though the chipset
	 * documentation doesn't mention it, we need to enter "Config
	 * register write enable" mode to modify the ID registers.
	 */
	CSR_WRITE_1(sc, RL_EECMD, RL_EEMODE_WRITECFG);
	bzero(eaddr, sizeof(eaddr));
	bcopy(IF_LLADDR(sc->rl_ifp), eaddr, ETHER_ADDR_LEN);
	CSR_WRITE_STREAM_4(sc, RL_IDR0, eaddr[0]);
	CSR_WRITE_STREAM_4(sc, RL_IDR4, eaddr[1]);
	CSR_WRITE_1(sc, RL_EECMD, RL_EEMODE_OFF);

	/* Init the RX memory block pointer register. */
	CSR_WRITE_4(sc, RL_RXADDR, sc->rl_cdata.rl_rx_buf_paddr +
	    RL_RX_8139_BUF_RESERVE);
	/* Init TX descriptors. */
	rl_list_tx_init(sc);
	/* Init Rx memory block. */
	rl_list_rx_init(sc);

	/*
	 * Enable transmit and receive.
	 */
	CSR_WRITE_1(sc, RL_COMMAND, RL_CMD_TX_ENB|RL_CMD_RX_ENB);

	/*
	 * Set the initial TX and RX configuration.
	 */
	CSR_WRITE_4(sc, RL_TXCFG, RL_TXCFG_CONFIG);
	CSR_WRITE_4(sc, RL_RXCFG, RL_RXCFG_CONFIG);

	/* Set RX filter. */
	rl_rxfilter(sc);

#ifdef DEVICE_POLLING
	/* Disable interrupts if we are polling. */
	if (ifp->if_capenable & IFCAP_POLLING)
		CSR_WRITE_2(sc, RL_IMR, 0);
	else
#endif
	/* Enable interrupts. */
	CSR_WRITE_2(sc, RL_IMR, RL_INTRS);

	/* Set initial TX threshold */
	sc->rl_txthresh = RL_TX_THRESH_INIT;

	/* Start RX/TX process. */
	CSR_WRITE_4(sc, RL_MISSEDPKT, 0);

	/* Enable receiver and transmitter. */
	CSR_WRITE_1(sc, RL_COMMAND, RL_CMD_TX_ENB|RL_CMD_RX_ENB);

	sc->rl_flags &= ~RL_FLAG_LINK;
	mii_mediachg(mii);

	CSR_WRITE_1(sc, sc->rl_cfg1, RL_CFG1_DRVLOAD|RL_CFG1_FULLDUPLEX);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	callout_reset(&sc->rl_stat_callout, hz, rl_tick, sc);
}