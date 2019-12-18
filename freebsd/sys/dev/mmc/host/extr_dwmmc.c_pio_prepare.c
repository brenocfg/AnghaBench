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
struct mmc_data {scalar_t__ xfer_len; } ;
struct mmc_command {struct mmc_data* data; } ;
struct dwmmc_softc {int fifo_depth; } ;

/* Variables and functions */
 int DEF_MSIZE ; 
 int /*<<< orphan*/  SDMMC_FIFOTH ; 
 int SDMMC_FIFOTH_MSIZE_S ; 
 int SDMMC_FIFOTH_RXWMARK_S ; 
 int SDMMC_FIFOTH_TXWMARK_S ; 
 int /*<<< orphan*/  WRITE4 (struct dwmmc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
pio_prepare(struct dwmmc_softc *sc, struct mmc_command *cmd)
{
	struct mmc_data *data;
	int reg;

	data = cmd->data;
	data->xfer_len = 0;

	reg = (DEF_MSIZE << SDMMC_FIFOTH_MSIZE_S);
	reg |= ((sc->fifo_depth / 2) - 1) << SDMMC_FIFOTH_RXWMARK_S;
	reg |= (sc->fifo_depth / 2) << SDMMC_FIFOTH_TXWMARK_S;

	WRITE4(sc, SDMMC_FIFOTH, reg);
	wmb();

	return (0);
}