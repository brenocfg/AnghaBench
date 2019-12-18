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
typedef  int uint32_t ;
struct mmc_data {scalar_t__ len; int flags; } ;
struct aml8726_sdxc_softc {int auto_fill_flush; int /*<<< orphan*/  dev; TYPE_1__* cmd; } ;
struct TYPE_2__ {struct mmc_data* data; } ;

/* Variables and functions */
 int AML_SDXC_PDMA_DMA_EN ; 
 int /*<<< orphan*/  AML_SDXC_PDMA_REG ; 
 int AML_SDXC_PDMA_RX_FLUSH_MODE_SW ; 
 int AML_SDXC_PDMA_TX_FILL ; 
 int /*<<< orphan*/  AML_SDXC_STATUS_REG ; 
 int AML_SDXC_STATUS_TX_CNT_MASK ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
aml8726_sdxc_engage_dma(struct aml8726_sdxc_softc *sc)
{
	int i;
	uint32_t pdmar;
	uint32_t sr;
	struct mmc_data *data;

	data = sc->cmd->data;

	if (data == NULL || data->len == 0)
		return;

	/*
	 * Engaging the DMA hardware is recommended before writing
	 * to AML_SDXC_SEND_REG so that the FIFOs are ready to go.
	 *
	 * Presumably AML_SDXC_CNTRL_REG and AML_SDXC_DMA_ADDR_REG
	 * must be set up prior to this happening.
	 */

	pdmar = CSR_READ_4(sc, AML_SDXC_PDMA_REG);

	pdmar &= ~AML_SDXC_PDMA_RX_FLUSH_MODE_SW;
	pdmar |= AML_SDXC_PDMA_DMA_EN;

	if (sc->auto_fill_flush == true) {
		CSR_WRITE_4(sc, AML_SDXC_PDMA_REG, pdmar);
		CSR_BARRIER(sc, AML_SDXC_PDMA_REG);
		return;
	}

	if ((data->flags & MMC_DATA_READ) != 0) {
		pdmar |= AML_SDXC_PDMA_RX_FLUSH_MODE_SW;
		CSR_WRITE_4(sc, AML_SDXC_PDMA_REG, pdmar);
		CSR_BARRIER(sc, AML_SDXC_PDMA_REG);
	} else {
		pdmar |= AML_SDXC_PDMA_TX_FILL;
		CSR_WRITE_4(sc, AML_SDXC_PDMA_REG, pdmar);
		CSR_BARRIER(sc, AML_SDXC_PDMA_REG);

		/*
		 * Wait up to 100us for data to show up.
		 */
		for (i = 0; i < 100; i++) {
			sr = CSR_READ_4(sc, AML_SDXC_STATUS_REG);
			if ((sr & AML_SDXC_STATUS_TX_CNT_MASK) != 0)
				break;
			DELAY(1);
		}
		if (i >= 100)
			device_printf(sc->dev, "TX FIFO fill timeout\n");
	}
}