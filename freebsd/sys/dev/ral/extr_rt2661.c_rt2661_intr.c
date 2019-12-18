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
struct rt2661_softc {int sc_flags; int /*<<< orphan*/ * txq; int /*<<< orphan*/  mgtq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK (struct rt2661_softc*) ; 
 int RAL_READ (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int RAL_RUNNING ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct rt2661_softc*) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2661_INT_MASK_CSR ; 
 int /*<<< orphan*/  RT2661_INT_SOURCE_CSR ; 
 int RT2661_MCU_BEACON_EXPIRE ; 
 int RT2661_MCU_CMD_DONE ; 
 int /*<<< orphan*/  RT2661_MCU_INT_MASK_CSR ; 
 int /*<<< orphan*/  RT2661_MCU_INT_SOURCE_CSR ; 
 int RT2661_MCU_WAKEUP ; 
 int RT2661_MGT_DONE ; 
 int RT2661_RX_DONE ; 
 int RT2661_TX0_DMA_DONE ; 
 int RT2661_TX1_DMA_DONE ; 
 int RT2661_TX2_DMA_DONE ; 
 int RT2661_TX3_DMA_DONE ; 
 int RT2661_TX_DONE ; 
 int /*<<< orphan*/  rt2661_mcu_beacon_expire (struct rt2661_softc*) ; 
 int /*<<< orphan*/  rt2661_mcu_cmd_intr (struct rt2661_softc*) ; 
 int /*<<< orphan*/  rt2661_mcu_wakeup (struct rt2661_softc*) ; 
 int /*<<< orphan*/  rt2661_rx_intr (struct rt2661_softc*) ; 
 int /*<<< orphan*/  rt2661_tx_dma_intr (struct rt2661_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2661_tx_intr (struct rt2661_softc*) ; 

void
rt2661_intr(void *arg)
{
	struct rt2661_softc *sc = arg;
	uint32_t r1, r2;

	RAL_LOCK(sc);

	/* disable MAC and MCU interrupts */
	RAL_WRITE(sc, RT2661_INT_MASK_CSR, 0xffffff7f);
	RAL_WRITE(sc, RT2661_MCU_INT_MASK_CSR, 0xffffffff);

	/* don't re-enable interrupts if we're shutting down */
	if (!(sc->sc_flags & RAL_RUNNING)) {
		RAL_UNLOCK(sc);
		return;
	}

	r1 = RAL_READ(sc, RT2661_INT_SOURCE_CSR);
	RAL_WRITE(sc, RT2661_INT_SOURCE_CSR, r1);

	r2 = RAL_READ(sc, RT2661_MCU_INT_SOURCE_CSR);
	RAL_WRITE(sc, RT2661_MCU_INT_SOURCE_CSR, r2);

	if (r1 & RT2661_MGT_DONE)
		rt2661_tx_dma_intr(sc, &sc->mgtq);

	if (r1 & RT2661_RX_DONE)
		rt2661_rx_intr(sc);

	if (r1 & RT2661_TX0_DMA_DONE)
		rt2661_tx_dma_intr(sc, &sc->txq[0]);

	if (r1 & RT2661_TX1_DMA_DONE)
		rt2661_tx_dma_intr(sc, &sc->txq[1]);

	if (r1 & RT2661_TX2_DMA_DONE)
		rt2661_tx_dma_intr(sc, &sc->txq[2]);

	if (r1 & RT2661_TX3_DMA_DONE)
		rt2661_tx_dma_intr(sc, &sc->txq[3]);

	if (r1 & RT2661_TX_DONE)
		rt2661_tx_intr(sc);

	if (r2 & RT2661_MCU_CMD_DONE)
		rt2661_mcu_cmd_intr(sc);

	if (r2 & RT2661_MCU_BEACON_EXPIRE)
		rt2661_mcu_beacon_expire(sc);

	if (r2 & RT2661_MCU_WAKEUP)
		rt2661_mcu_wakeup(sc);

	/* re-enable MAC and MCU interrupts */
	RAL_WRITE(sc, RT2661_INT_MASK_CSR, 0x0000ff10);
	RAL_WRITE(sc, RT2661_MCU_INT_MASK_CSR, 0);

	RAL_UNLOCK(sc);
}