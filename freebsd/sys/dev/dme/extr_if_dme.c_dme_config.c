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
struct dme_softc {scalar_t__ dme_rev; int* dme_macaddr; int /*<<< orphan*/  dme_dev; } ;

/* Variables and functions */
 int BMCR_RESET ; 
 int BPTR_BPHW (int) ; 
 int BPTR_JPT (int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DME_BPTR ; 
 scalar_t__ DME_CHIP_DM9000B ; 
 int /*<<< orphan*/  DME_FCR ; 
 int /*<<< orphan*/  DME_FCTR ; 
 int /*<<< orphan*/  DME_GPCR ; 
 int /*<<< orphan*/  DME_GPR ; 
 int /*<<< orphan*/  DME_IMR ; 
 int /*<<< orphan*/  DME_INT_PHY ; 
 int /*<<< orphan*/  DME_ISR ; 
 int /*<<< orphan*/  DME_MAR (int) ; 
 int /*<<< orphan*/  DME_NCR ; 
 int /*<<< orphan*/  DME_NSR ; 
 int /*<<< orphan*/  DME_PAR (int) ; 
 int /*<<< orphan*/  DME_RCR ; 
 int /*<<< orphan*/  DME_SMCR ; 
 int /*<<< orphan*/  DME_TCR ; 
 int DSPCR_INIT ; 
 int ETHER_ADDR_LEN ; 
 int FCTR_HWOT (int) ; 
 int FCTR_LWOT (int) ; 
 int IMR_PAR ; 
 int IMR_PRI ; 
 int IMR_PTI ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_DME_DSPCR ; 
 int NCR_LBK_NORMAL ; 
 int NSR_TX1END ; 
 int NSR_TX2END ; 
 int NSR_WAKEST ; 
 int RCR_DIS_CRC ; 
 int RCR_DIS_LONG ; 
 int RCR_RXEN ; 
 int dme_miibus_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme_miibus_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dme_write_reg (struct dme_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dme_config(struct dme_softc *sc)
{
	int i;

	/* Mask all interrupts and reset receive pointer */
	dme_write_reg(sc, DME_IMR, IMR_PAR);

	/* Disable GPIO0 to enable the internal PHY */
	dme_write_reg(sc, DME_GPCR, 1);
	dme_write_reg(sc, DME_GPR, 0);

#if 0
	/*
	 * Supposedly requires special initialization for DSP PHYs
	 * used by DM9000B. Maybe belongs in dedicated PHY driver?
	 */
	if (sc->dme_rev == DME_CHIP_DM9000B) {
		dme_miibus_writereg(sc->dme_dev, DME_INT_PHY, MII_BMCR,
		    BMCR_RESET);
		dme_miibus_writereg(sc->dme_dev, DME_INT_PHY, MII_DME_DSPCR,
		    DSPCR_INIT);
		/* Wait 100ms for it to complete. */
		for (i = 0; i < 100; i++) {
			int reg;

			reg = dme_miibus_readreg(sc->dme_dev, DME_INT_PHY, MII_BMCR);
			if ((reg & BMCR_RESET) == 0)
				break;
			DELAY(1000);
		}
	}
#endif

	/* Select the internal PHY and normal loopback */
	dme_write_reg(sc, DME_NCR, NCR_LBK_NORMAL);
	/* Clear any TX requests */
	dme_write_reg(sc, DME_TCR, 0);
	/* Setup backpressure thresholds to 4k and 600us */
	dme_write_reg(sc, DME_BPTR, BPTR_BPHW(3) | BPTR_JPT(0x0f));
	/* Setup flow control */
	dme_write_reg(sc, DME_FCTR, FCTR_HWOT(0x3) | FCTR_LWOT(0x08));
	/* Enable flow control */
	dme_write_reg(sc, DME_FCR, 0xff);
	/* Clear special modes */
	dme_write_reg(sc, DME_SMCR, 0);
	/* Clear TX status */
	dme_write_reg(sc, DME_NSR, NSR_WAKEST | NSR_TX2END | NSR_TX1END);
	/* Clear interrrupts */
	dme_write_reg(sc, DME_ISR, 0xff);
	/* Set multicast address filter */
	for (i = 0; i < 8; i++)
		dme_write_reg(sc, DME_MAR(i), 0xff);
	/* Set the MAC address */
	for (i = 0; i < ETHER_ADDR_LEN; i++)
		dme_write_reg(sc, DME_PAR(i), sc->dme_macaddr[i]);
	/* Enable the RX buffer */
	dme_write_reg(sc, DME_RCR, RCR_DIS_LONG | RCR_DIS_CRC | RCR_RXEN);

	/* Enable interrupts we care about */
	dme_write_reg(sc, DME_IMR, IMR_PAR | IMR_PRI | IMR_PTI);
}