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
struct mii_data {int /*<<< orphan*/  mii_media_active; } ;
struct jme_softc {int jme_flags; scalar_t__ jme_rev; scalar_t__ jme_chip_rev; int /*<<< orphan*/  jme_phyaddr; int /*<<< orphan*/  jme_dev; int /*<<< orphan*/  jme_miibus; } ;

/* Variables and functions */
 int CSR_READ_4 (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ DEVICEID_JMC250 ; 
 scalar_t__ DEVICEREVID_JMC250_A2 ; 
 int GHC_FULL_DUPLEX ; 
 int GHC_RESET ; 
 int GHC_SPEED_10 ; 
 int GHC_SPEED_100 ; 
 int GHC_SPEED_1000 ; 
 int GHC_TX_MAC_CLK_100 ; 
 int GHC_TX_MAC_CLK_1000 ; 
 int GHC_TX_OFFLD_CLK_100 ; 
 int GHC_TX_OFFLD_CLK_1000 ; 
 int GPREG1_HDPX_FIX ; 
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int const IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int JME_FLAG_FASTETH ; 
 int JME_FLAG_TXCLK ; 
 int /*<<< orphan*/  JME_GHC ; 
 int /*<<< orphan*/  JME_GPREG1 ; 
 int /*<<< orphan*/  JME_LOCK_ASSERT (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_RXMAC ; 
 int /*<<< orphan*/  JME_TXMAC ; 
 int /*<<< orphan*/  JME_TXPFC ; 
 int /*<<< orphan*/  JME_TXTRHD ; 
 int RXMAC_COLL_DET_ENB ; 
 int RXMAC_FC_ENB ; 
 int TXMAC_BACKOFF ; 
 int TXMAC_CARRIER_EXT ; 
 int TXMAC_CARRIER_SENSE ; 
 int TXMAC_COLL_ENB ; 
 int TXMAC_FRAME_BURST ; 
 int TXPFC_PAUSE_ENB ; 
 int TXTRHD_RT_LIMIT_ENB ; 
 int TXTRHD_RT_PERIOD_ENB ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_miibus_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
jme_mac_config(struct jme_softc *sc)
{
	struct mii_data *mii;
	uint32_t ghc, gpreg, rxmac, txmac, txpause;
	uint32_t txclk;

	JME_LOCK_ASSERT(sc);

	mii = device_get_softc(sc->jme_miibus);

	CSR_WRITE_4(sc, JME_GHC, GHC_RESET);
	DELAY(10);
	CSR_WRITE_4(sc, JME_GHC, 0);
	ghc = 0;
	txclk = 0;
	rxmac = CSR_READ_4(sc, JME_RXMAC);
	rxmac &= ~RXMAC_FC_ENB;
	txmac = CSR_READ_4(sc, JME_TXMAC);
	txmac &= ~(TXMAC_CARRIER_EXT | TXMAC_FRAME_BURST);
	txpause = CSR_READ_4(sc, JME_TXPFC);
	txpause &= ~TXPFC_PAUSE_ENB;
	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0) {
		ghc |= GHC_FULL_DUPLEX;
		rxmac &= ~RXMAC_COLL_DET_ENB;
		txmac &= ~(TXMAC_COLL_ENB | TXMAC_CARRIER_SENSE |
		    TXMAC_BACKOFF | TXMAC_CARRIER_EXT |
		    TXMAC_FRAME_BURST);
		if ((IFM_OPTIONS(mii->mii_media_active) & IFM_ETH_TXPAUSE) != 0)
			txpause |= TXPFC_PAUSE_ENB;
		if ((IFM_OPTIONS(mii->mii_media_active) & IFM_ETH_RXPAUSE) != 0)
			rxmac |= RXMAC_FC_ENB;
		/* Disable retry transmit timer/retry limit. */
		CSR_WRITE_4(sc, JME_TXTRHD, CSR_READ_4(sc, JME_TXTRHD) &
		    ~(TXTRHD_RT_PERIOD_ENB | TXTRHD_RT_LIMIT_ENB));
	} else {
		rxmac |= RXMAC_COLL_DET_ENB;
		txmac |= TXMAC_COLL_ENB | TXMAC_CARRIER_SENSE | TXMAC_BACKOFF;
		/* Enable retry transmit timer/retry limit. */
		CSR_WRITE_4(sc, JME_TXTRHD, CSR_READ_4(sc, JME_TXTRHD) |
		    TXTRHD_RT_PERIOD_ENB | TXTRHD_RT_LIMIT_ENB);
	}
		/* Reprogram Tx/Rx MACs with resolved speed/duplex. */
	switch (IFM_SUBTYPE(mii->mii_media_active)) {
	case IFM_10_T:
		ghc |= GHC_SPEED_10;
		txclk |= GHC_TX_OFFLD_CLK_100 | GHC_TX_MAC_CLK_100;
		break;
	case IFM_100_TX:
		ghc |= GHC_SPEED_100;
		txclk |= GHC_TX_OFFLD_CLK_100 | GHC_TX_MAC_CLK_100;
		break;
	case IFM_1000_T:
		if ((sc->jme_flags & JME_FLAG_FASTETH) != 0)
			break;
		ghc |= GHC_SPEED_1000;
		txclk |= GHC_TX_OFFLD_CLK_1000 | GHC_TX_MAC_CLK_1000;
		if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) == 0)
			txmac |= TXMAC_CARRIER_EXT | TXMAC_FRAME_BURST;
		break;
	default:
		break;
	}
	if (sc->jme_rev == DEVICEID_JMC250 &&
	    sc->jme_chip_rev == DEVICEREVID_JMC250_A2) {
		/*
		 * Workaround occasional packet loss issue of JMC250 A2
		 * when it runs on half-duplex media.
		 */
		gpreg = CSR_READ_4(sc, JME_GPREG1);
		if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0)
			gpreg &= ~GPREG1_HDPX_FIX;
		else
			gpreg |= GPREG1_HDPX_FIX;
		CSR_WRITE_4(sc, JME_GPREG1, gpreg);
		/* Workaround CRC errors at 100Mbps on JMC250 A2. */
		if (IFM_SUBTYPE(mii->mii_media_active) == IFM_100_TX) {
			/* Extend interface FIFO depth. */
			jme_miibus_writereg(sc->jme_dev, sc->jme_phyaddr,
			    0x1B, 0x0000);
		} else {
			/* Select default interface FIFO depth. */
			jme_miibus_writereg(sc->jme_dev, sc->jme_phyaddr,
			    0x1B, 0x0004);
		}
	}
	if ((sc->jme_flags & JME_FLAG_TXCLK) != 0)
		ghc |= txclk;
	CSR_WRITE_4(sc, JME_GHC, ghc);
	CSR_WRITE_4(sc, JME_RXMAC, rxmac);
	CSR_WRITE_4(sc, JME_TXMAC, txmac);
	CSR_WRITE_4(sc, JME_TXPFC, txpause);
}