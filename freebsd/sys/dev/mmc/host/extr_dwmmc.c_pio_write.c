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
struct mmc_data {int flags; int xfer_len; int len; scalar_t__ data; } ;
struct mmc_command {struct mmc_data* data; } ;
struct dwmmc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MMC_DATA_WRITE ; 
 int READ4 (struct dwmmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMMC_DATA ; 
 int /*<<< orphan*/  SDMMC_INTMASK_TXDR ; 
 int /*<<< orphan*/  SDMMC_RINTSTS ; 
 int /*<<< orphan*/  SDMMC_STATUS ; 
 int SDMMC_STATUS_FIFO_FULL ; 
 int /*<<< orphan*/  WRITE4 (struct dwmmc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pio_write(struct dwmmc_softc *sc, struct mmc_command *cmd)
{
	struct mmc_data *data;
	uint32_t *p, status;

	if (cmd == NULL || cmd->data == NULL)
		return;

	data = cmd->data;
	if ((data->flags & MMC_DATA_WRITE) == 0)
		return;

	KASSERT((data->xfer_len & 3) == 0, ("xfer_len not aligned"));
	p = (uint32_t *)data->data + (data->xfer_len >> 2);

	while (data->xfer_len < data->len) {
		status = READ4(sc, SDMMC_STATUS);
		if (status & SDMMC_STATUS_FIFO_FULL)
			break;
		WRITE4(sc, SDMMC_DATA, *p++);
		data->xfer_len += 4;
	}

	WRITE4(sc, SDMMC_RINTSTS, SDMMC_INTMASK_TXDR);
}