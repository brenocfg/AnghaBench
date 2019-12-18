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
struct TYPE_2__ {int /*<<< orphan*/  callout; } ;
struct cpsw_softc {TYPE_1__ watchdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_CPDMA_RX_CONTROL ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_CP (int) ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_HDP (int) ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_INTMASK_CLEAR ; 
 int /*<<< orphan*/  CPSW_CPDMA_SOFT_RESET ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_CONTROL ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_CP (int) ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_HDP (int) ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_INTMASK_CLEAR ; 
 int /*<<< orphan*/  CPSW_SL_SOFT_RESET (int) ; 
 int /*<<< orphan*/  CPSW_SS_SOFT_RESET ; 
 int /*<<< orphan*/  CPSW_WR_C_MISC_EN (int) ; 
 int /*<<< orphan*/  CPSW_WR_C_RX_EN (int) ; 
 int /*<<< orphan*/  CPSW_WR_C_RX_THRESH_EN (int) ; 
 int /*<<< orphan*/  CPSW_WR_C_TX_EN (int) ; 
 int /*<<< orphan*/  CPSW_WR_SOFT_RESET ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int cpsw_read_4 (struct cpsw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_write_4 (struct cpsw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cpsw_reset(struct cpsw_softc *sc)
{
	int i;

	callout_stop(&sc->watchdog.callout);

	/* Reset RMII/RGMII wrapper. */
	cpsw_write_4(sc, CPSW_WR_SOFT_RESET, 1);
	while (cpsw_read_4(sc, CPSW_WR_SOFT_RESET) & 1)
		;

	/* Disable TX and RX interrupts for all cores. */
	for (i = 0; i < 3; ++i) {
		cpsw_write_4(sc, CPSW_WR_C_RX_THRESH_EN(i), 0x00);
		cpsw_write_4(sc, CPSW_WR_C_TX_EN(i), 0x00);
		cpsw_write_4(sc, CPSW_WR_C_RX_EN(i), 0x00);
		cpsw_write_4(sc, CPSW_WR_C_MISC_EN(i), 0x00);
	}

	/* Reset CPSW subsystem. */
	cpsw_write_4(sc, CPSW_SS_SOFT_RESET, 1);
	while (cpsw_read_4(sc, CPSW_SS_SOFT_RESET) & 1)
		;

	/* Reset Sliver port 1 and 2 */
	for (i = 0; i < 2; i++) {
		/* Reset */
		cpsw_write_4(sc, CPSW_SL_SOFT_RESET(i), 1);
		while (cpsw_read_4(sc, CPSW_SL_SOFT_RESET(i)) & 1)
			;
	}

	/* Reset DMA controller. */
	cpsw_write_4(sc, CPSW_CPDMA_SOFT_RESET, 1);
	while (cpsw_read_4(sc, CPSW_CPDMA_SOFT_RESET) & 1)
		;

	/* Disable TX & RX DMA */
	cpsw_write_4(sc, CPSW_CPDMA_TX_CONTROL, 0);
	cpsw_write_4(sc, CPSW_CPDMA_RX_CONTROL, 0);

	/* Clear all queues. */
	for (i = 0; i < 8; i++) {
		cpsw_write_4(sc, CPSW_CPDMA_TX_HDP(i), 0);
		cpsw_write_4(sc, CPSW_CPDMA_RX_HDP(i), 0);
		cpsw_write_4(sc, CPSW_CPDMA_TX_CP(i), 0);
		cpsw_write_4(sc, CPSW_CPDMA_RX_CP(i), 0);
	}

	/* Clear all interrupt Masks */
	cpsw_write_4(sc, CPSW_CPDMA_RX_INTMASK_CLEAR, 0xFFFFFFFF);
	cpsw_write_4(sc, CPSW_CPDMA_TX_INTMASK_CLEAR, 0xFFFFFFFF);
}