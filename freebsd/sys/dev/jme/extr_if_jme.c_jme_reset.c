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
struct jme_softc {int jme_flags; } ;

/* Variables and functions */
 int CSR_READ_4 (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int GHC_RESET ; 
 int GHC_TX_MAC_CLK_DIS ; 
 int GPREG1_RX_MAC_CLK_DIS ; 
 int JME_FLAG_RXCLK ; 
 int JME_FLAG_TXCLK ; 
 int /*<<< orphan*/  JME_GHC ; 
 int /*<<< orphan*/  JME_GPREG1 ; 
 int /*<<< orphan*/  jme_stop_rx (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_stop_tx (struct jme_softc*) ; 

__attribute__((used)) static void
jme_reset(struct jme_softc *sc)
{
	uint32_t ghc, gpreg;

	/* Stop receiver, transmitter. */
	jme_stop_rx(sc);
	jme_stop_tx(sc);

	/* Reset controller. */
	CSR_WRITE_4(sc, JME_GHC, GHC_RESET);
	CSR_READ_4(sc, JME_GHC);
	DELAY(10);
	/*
	 * Workaround Rx FIFO overruns seen under certain conditions.
	 * Explicitly synchorize TX/RX clock.  TX/RX clock should be
	 * enabled only after enabling TX/RX MACs.
	 */
	if ((sc->jme_flags & (JME_FLAG_TXCLK | JME_FLAG_RXCLK)) != 0) {
		/* Disable TX clock. */
		CSR_WRITE_4(sc, JME_GHC, GHC_RESET | GHC_TX_MAC_CLK_DIS);
		/* Disable RX clock. */
		gpreg = CSR_READ_4(sc, JME_GPREG1);
		CSR_WRITE_4(sc, JME_GPREG1, gpreg | GPREG1_RX_MAC_CLK_DIS);
		gpreg = CSR_READ_4(sc, JME_GPREG1);
		/* De-assert RESET but still disable TX clock. */
		CSR_WRITE_4(sc, JME_GHC, GHC_TX_MAC_CLK_DIS);
		ghc = CSR_READ_4(sc, JME_GHC);

		/* Enable TX clock. */
		CSR_WRITE_4(sc, JME_GHC, ghc & ~GHC_TX_MAC_CLK_DIS);
		/* Enable RX clock. */
		CSR_WRITE_4(sc, JME_GPREG1, gpreg & ~GPREG1_RX_MAC_CLK_DIS);
		CSR_READ_4(sc, JME_GPREG1);

		/* Disable TX/RX clock again. */
		CSR_WRITE_4(sc, JME_GHC, GHC_TX_MAC_CLK_DIS);
		CSR_WRITE_4(sc, JME_GPREG1, gpreg | GPREG1_RX_MAC_CLK_DIS);
	} else
		CSR_WRITE_4(sc, JME_GHC, 0);
	CSR_READ_4(sc, JME_GHC);
	DELAY(10);
}