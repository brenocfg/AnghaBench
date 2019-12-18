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
struct smc_softc {int smc_mask; struct ifnet* smc_ifp; } ;
struct ifnet {int if_capenable; } ;

/* Variables and functions */
 int EPH_INT ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  MSK ; 
 int /*<<< orphan*/  RCR ; 
 int RCR_RXEN ; 
 int RCR_STRIP_CRC ; 
 int RCV_INT ; 
 int /*<<< orphan*/  RPCR ; 
 int RPCR_ANEG ; 
 int RPCR_LED_ACT_ANY ; 
 int RPCR_LED_LINK_ANY ; 
 int RPCR_LSA_SHIFT ; 
 int RPCR_LSB_SHIFT ; 
 int RX_OVRN_INT ; 
 int /*<<< orphan*/  SMC_ASSERT_LOCKED (struct smc_softc*) ; 
 int /*<<< orphan*/  TCR ; 
 int TCR_PAD_EN ; 
 int TCR_TXENA ; 
 int TX_INT ; 
 int /*<<< orphan*/  smc_select_bank (struct smc_softc*,int) ; 
 int /*<<< orphan*/  smc_write_1 (struct smc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smc_write_2 (struct smc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
smc_enable(struct smc_softc *sc)
{
	struct ifnet		*ifp;

	SMC_ASSERT_LOCKED(sc);
	ifp = sc->smc_ifp;

	/*
	 * Set up the receive/PHY control register.
	 */
	smc_select_bank(sc, 0);
	smc_write_2(sc, RPCR, RPCR_ANEG | (RPCR_LED_LINK_ANY << RPCR_LSA_SHIFT)
	    | (RPCR_LED_ACT_ANY << RPCR_LSB_SHIFT));

	/*
	 * Set up the transmit and receive control registers.
	 */
	smc_write_2(sc, TCR, TCR_TXENA | TCR_PAD_EN);
	smc_write_2(sc, RCR, RCR_RXEN | RCR_STRIP_CRC);

	/*
	 * Set up the interrupt mask.
	 */
	smc_select_bank(sc, 2);
	sc->smc_mask = EPH_INT | RX_OVRN_INT | RCV_INT | TX_INT;
	if ((ifp->if_capenable & IFCAP_POLLING) != 0)
		smc_write_1(sc, MSK, sc->smc_mask);
}