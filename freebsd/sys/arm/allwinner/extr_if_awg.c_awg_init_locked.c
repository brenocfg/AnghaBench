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
struct mii_data {int dummy; } ;
struct awg_softc {int /*<<< orphan*/  stat_ch; int /*<<< orphan*/  ifp; int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_ASSERT_LOCKED (struct awg_softc*) ; 
 int BASIC_CTL_BURST_LEN_SHIFT ; 
 int BASIC_CTL_RX_TX_PRI ; 
 int CHECK_CRC ; 
 int /*<<< orphan*/  EMAC_BASIC_CTL_1 ; 
 int /*<<< orphan*/  EMAC_RX_CTL_0 ; 
 int /*<<< orphan*/  EMAC_RX_CTL_1 ; 
 int /*<<< orphan*/  EMAC_TX_CTL_0 ; 
 int /*<<< orphan*/  EMAC_TX_CTL_1 ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int RD4 (struct awg_softc*,int /*<<< orphan*/ ) ; 
 int RX_DMA_EN ; 
 int RX_EN ; 
 int RX_MD ; 
 int TX_DMA_EN ; 
 int TX_EN ; 
 int TX_MD ; 
 int TX_NEXT_FRAME ; 
 int /*<<< orphan*/  WR4 (struct awg_softc*,int /*<<< orphan*/ ,int) ; 
 int awg_burst_len ; 
 int /*<<< orphan*/  awg_disable_intr (struct awg_softc*) ; 
 int /*<<< orphan*/  awg_enable_intr (struct awg_softc*) ; 
 scalar_t__ awg_rx_tx_pri ; 
 int /*<<< orphan*/  awg_setup_rxfilter (struct awg_softc*) ; 
 int /*<<< orphan*/  awg_tick ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct awg_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static void
awg_init_locked(struct awg_softc *sc)
{
	struct mii_data *mii;
	uint32_t val;
	if_t ifp;

	mii = device_get_softc(sc->miibus);
	ifp = sc->ifp;

	AWG_ASSERT_LOCKED(sc);

	if (if_getdrvflags(ifp) & IFF_DRV_RUNNING)
		return;

	awg_setup_rxfilter(sc);

	/* Configure DMA burst length and priorities */
	val = awg_burst_len << BASIC_CTL_BURST_LEN_SHIFT;
	if (awg_rx_tx_pri)
		val |= BASIC_CTL_RX_TX_PRI;
	WR4(sc, EMAC_BASIC_CTL_1, val);

	/* Enable interrupts */
#ifdef DEVICE_POLLING
	if ((if_getcapenable(ifp) & IFCAP_POLLING) == 0)
		awg_enable_intr(sc);
	else
		awg_disable_intr(sc);
#else
	awg_enable_intr(sc);
#endif

	/* Enable transmit DMA */
	val = RD4(sc, EMAC_TX_CTL_1);
	WR4(sc, EMAC_TX_CTL_1, val | TX_DMA_EN | TX_MD | TX_NEXT_FRAME);

	/* Enable receive DMA */
	val = RD4(sc, EMAC_RX_CTL_1);
	WR4(sc, EMAC_RX_CTL_1, val | RX_DMA_EN | RX_MD);

	/* Enable transmitter */
	val = RD4(sc, EMAC_TX_CTL_0);
	WR4(sc, EMAC_TX_CTL_0, val | TX_EN);

	/* Enable receiver */
	val = RD4(sc, EMAC_RX_CTL_0);
	WR4(sc, EMAC_RX_CTL_0, val | RX_EN | CHECK_CRC);

	if_setdrvflagbits(ifp, IFF_DRV_RUNNING, IFF_DRV_OACTIVE);

	mii_mediachg(mii);
	callout_reset(&sc->stat_ch, hz, awg_tick, sc);
}