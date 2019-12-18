#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int error; } ;
struct aml8726_sdxc_softc {int /*<<< orphan*/  ch; TYPE_2__ busy; TYPE_1__* cmd; } ;
struct TYPE_3__ {int* resp; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_SDXC_BUSY_POLL_INTVL ; 
 int /*<<< orphan*/  AML_SDXC_CMD_ARGUMENT_REG ; 
 int AML_SDXC_IRQ_ENABLE_A_PKG_CRC_ERR ; 
 int AML_SDXC_IRQ_ENABLE_A_PKG_TIMEOUT_ERR ; 
 int AML_SDXC_IRQ_ENABLE_RESP_CRC_ERR ; 
 int AML_SDXC_IRQ_ENABLE_RESP_TIMEOUT_ERR ; 
 int AML_SDXC_IRQ_STATUS_CLEAR ; 
 int AML_SDXC_IRQ_STATUS_DMA_DONE ; 
 int /*<<< orphan*/  AML_SDXC_IRQ_STATUS_REG ; 
 int AML_SDXC_IRQ_STATUS_RESP_OK ; 
 int AML_SDXC_IRQ_STATUS_RX_FIFO_FULL ; 
 int AML_SDXC_IRQ_STATUS_TRANSFER_DONE_OK ; 
 int AML_SDXC_IRQ_STATUS_TX_FIFO_EMPTY ; 
 int /*<<< orphan*/  AML_SDXC_LOCK (struct aml8726_sdxc_softc*) ; 
 int AML_SDXC_PDMA_DMA_EN ; 
 int /*<<< orphan*/  AML_SDXC_PDMA_REG ; 
 int AML_SDXC_PDMA_RESP_INDEX_MASK ; 
 int AML_SDXC_PDMA_RESP_INDEX_SHIFT ; 
 int AML_SDXC_SEND_CMD_HAS_RESP ; 
 int AML_SDXC_SEND_INDEX_MASK ; 
 int /*<<< orphan*/  AML_SDXC_SEND_REG ; 
 int AML_SDXC_SEND_RESP_136 ; 
 int AML_SDXC_STATUS_BUSY ; 
 int AML_SDXC_STATUS_DAT0 ; 
 int /*<<< orphan*/  AML_SDXC_STATUS_REG ; 
 int /*<<< orphan*/  AML_SDXC_UNLOCK (struct aml8726_sdxc_softc*) ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ,int) ; 
 int MMC_ERR_BADCRC ; 
 int MMC_ERR_FAILED ; 
 int MMC_ERR_FIFO ; 
 int MMC_ERR_NONE ; 
 int MMC_ERR_TIMEOUT ; 
 int MMC_RSP_BUSY ; 
 int MMC_STOP_TRANSMISSION ; 
 int /*<<< orphan*/  aml8726_sdxc_busy_check ; 
 int /*<<< orphan*/  aml8726_sdxc_disengage_dma (struct aml8726_sdxc_softc*) ; 
 int /*<<< orphan*/  aml8726_sdxc_finish_command (struct aml8726_sdxc_softc*,int) ; 
 int /*<<< orphan*/  aml8726_sdxc_soft_reset (struct aml8726_sdxc_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aml8726_sdxc_softc*) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  msecs_to_ticks (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aml8726_sdxc_intr(void *arg)
{
	struct aml8726_sdxc_softc *sc = (struct aml8726_sdxc_softc *)arg;
	uint32_t isr;
	uint32_t pdmar;
	uint32_t sndr;
	uint32_t sr;
	int i;
	int mmc_error;
	int start;
	int stop;

	AML_SDXC_LOCK(sc);

	isr = CSR_READ_4(sc, AML_SDXC_IRQ_STATUS_REG);
	sndr = CSR_READ_4(sc, AML_SDXC_SEND_REG);
	sr = CSR_READ_4(sc, AML_SDXC_STATUS_REG);

	if (sc->cmd == NULL)
		goto spurious;

	mmc_error = MMC_ERR_NONE;

	if ((isr & (AML_SDXC_IRQ_STATUS_TX_FIFO_EMPTY |
	    AML_SDXC_IRQ_STATUS_RX_FIFO_FULL)) != 0)
		mmc_error = MMC_ERR_FIFO;
	else if ((isr & (AML_SDXC_IRQ_ENABLE_A_PKG_CRC_ERR |
	    AML_SDXC_IRQ_ENABLE_RESP_CRC_ERR)) != 0)
		mmc_error = MMC_ERR_BADCRC;
	else if ((isr & (AML_SDXC_IRQ_ENABLE_A_PKG_TIMEOUT_ERR |
	    AML_SDXC_IRQ_ENABLE_RESP_TIMEOUT_ERR)) != 0)
		mmc_error = MMC_ERR_TIMEOUT;
	else if ((isr & (AML_SDXC_IRQ_STATUS_RESP_OK |
	    AML_SDXC_IRQ_STATUS_DMA_DONE |
	    AML_SDXC_IRQ_STATUS_TRANSFER_DONE_OK)) != 0) {
		;
	}
	else {
spurious:
		/*
		 * Clear spurious interrupts while leaving intacted any
		 * interrupts that may have occurred after we read the
		 * interrupt status register.
		 */

		CSR_WRITE_4(sc, AML_SDXC_IRQ_STATUS_REG,
		    (AML_SDXC_IRQ_STATUS_CLEAR & isr));
		CSR_BARRIER(sc, AML_SDXC_IRQ_STATUS_REG);
		AML_SDXC_UNLOCK(sc);
		return;
	}

	aml8726_sdxc_disengage_dma(sc);

	if ((sndr & AML_SDXC_SEND_CMD_HAS_RESP) != 0) {
		start = 0;
		stop = 1;
		if ((sndr & AML_SDXC_SEND_RESP_136) != 0) {
			start = 1;
			stop = start + 4;
		}
		for (i = start; i < stop; i++) {
			pdmar = CSR_READ_4(sc, AML_SDXC_PDMA_REG);
			pdmar &= ~(AML_SDXC_PDMA_DMA_EN |
			    AML_SDXC_PDMA_RESP_INDEX_MASK);
			pdmar |= i << AML_SDXC_PDMA_RESP_INDEX_SHIFT;
			CSR_WRITE_4(sc, AML_SDXC_PDMA_REG, pdmar);
			sc->cmd->resp[(stop - 1) - i] = CSR_READ_4(sc,
			    AML_SDXC_CMD_ARGUMENT_REG);
		}
	}

	if ((sr & AML_SDXC_STATUS_BUSY) != 0 &&
	    /*
	     * A multiblock operation may keep the hardware
	     * busy until stop transmission is executed.
	     */
	    (isr & (AML_SDXC_IRQ_STATUS_DMA_DONE |
	    AML_SDXC_IRQ_STATUS_TRANSFER_DONE_OK)) == 0) {
		if (mmc_error == MMC_ERR_NONE)
			mmc_error = MMC_ERR_FAILED;

		/*
		 * Issue a soft reset to terminate the command.
		 *
		 * Ensure the command has terminated before continuing on
		 * to things such as bus_dmamap_sync / bus_dmamap_unload.
		 */

		aml8726_sdxc_soft_reset(sc);

		while ((CSR_READ_4(sc, AML_SDXC_STATUS_REG) &
		    AML_SDXC_STATUS_BUSY) != 0)
			cpu_spinwait();
	}

	/*
	 * The stop command can be generated either manually or
	 * automatically by the hardware if MISC_MANUAL_STOP_MODE
	 * has not been set.  In either case check for busy.
	 */

	if (((sc->cmd->flags & MMC_RSP_BUSY) != 0 ||
	    (sndr & AML_SDXC_SEND_INDEX_MASK) == MMC_STOP_TRANSMISSION) &&
	    (sr & AML_SDXC_STATUS_DAT0) == 0) {
		sc->busy.error = mmc_error;
		callout_reset(&sc->ch,
		    msecs_to_ticks(AML_SDXC_BUSY_POLL_INTVL),
		    aml8726_sdxc_busy_check, sc);
		CSR_WRITE_4(sc, AML_SDXC_IRQ_STATUS_REG,
		    (AML_SDXC_IRQ_STATUS_CLEAR & isr));
		CSR_BARRIER(sc, AML_SDXC_IRQ_STATUS_REG);
		AML_SDXC_UNLOCK(sc);
		return;
	}

	aml8726_sdxc_finish_command(sc, mmc_error);
}