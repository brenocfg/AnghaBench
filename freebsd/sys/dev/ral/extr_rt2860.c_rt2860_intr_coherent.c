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
struct rt2860_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2860_RX_DMA_EN ; 
 int RT2860_TX_DMA_EN ; 
 int RT2860_TX_WB_DDONE ; 
 int /*<<< orphan*/  RT2860_WPDMA_GLO_CFG ; 
 int /*<<< orphan*/  rt2860_txrx_enable (struct rt2860_softc*) ; 

__attribute__((used)) static void
rt2860_intr_coherent(struct rt2860_softc *sc)
{
	uint32_t tmp;

	/* DMA finds data coherent event when checking the DDONE bit */

	DPRINTF(("Tx/Rx Coherent interrupt\n"));

	/* restart DMA engine */
	tmp = RAL_READ(sc, RT2860_WPDMA_GLO_CFG);
	tmp &= ~(RT2860_TX_WB_DDONE | RT2860_RX_DMA_EN | RT2860_TX_DMA_EN);
	RAL_WRITE(sc, RT2860_WPDMA_GLO_CFG, tmp);

	(void)rt2860_txrx_enable(sc);
}