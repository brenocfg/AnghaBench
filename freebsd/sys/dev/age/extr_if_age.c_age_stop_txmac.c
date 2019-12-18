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
struct age_softc {int /*<<< orphan*/  age_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_DMA_CFG ; 
 int /*<<< orphan*/  AGE_IDLE_STATUS ; 
 int /*<<< orphan*/  AGE_LOCK_ASSERT (struct age_softc*) ; 
 int /*<<< orphan*/  AGE_MAC_CFG ; 
 int AGE_RESET_TIMEOUT ; 
 int CSR_READ_4 (struct age_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct age_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int DMA_CFG_RD_ENB ; 
 int IDLE_STATUS_DMARD ; 
 int IDLE_STATUS_TXMAC ; 
 int MAC_CFG_TX_ENB ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
age_stop_txmac(struct age_softc *sc)
{
	uint32_t reg;
	int i;

	AGE_LOCK_ASSERT(sc);

	reg = CSR_READ_4(sc, AGE_MAC_CFG);
	if ((reg & MAC_CFG_TX_ENB) != 0) {
		reg &= ~MAC_CFG_TX_ENB;
		CSR_WRITE_4(sc, AGE_MAC_CFG, reg);
	}
	/* Stop Tx DMA engine. */
	reg = CSR_READ_4(sc, AGE_DMA_CFG);
	if ((reg & DMA_CFG_RD_ENB) != 0) {
		reg &= ~DMA_CFG_RD_ENB;
		CSR_WRITE_4(sc, AGE_DMA_CFG, reg);
	}
	for (i = AGE_RESET_TIMEOUT; i > 0; i--) {
		if ((CSR_READ_4(sc, AGE_IDLE_STATUS) &
		    (IDLE_STATUS_TXMAC | IDLE_STATUS_DMARD)) == 0)
			break;
		DELAY(10);
	}
	if (i == 0)
		device_printf(sc->age_dev, "stopping TxMAC timeout!\n");
}