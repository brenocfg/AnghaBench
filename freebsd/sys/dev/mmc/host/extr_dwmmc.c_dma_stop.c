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
struct dwmmc_softc {int dummy; } ;

/* Variables and functions */
 int READ4 (struct dwmmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMMC_BMOD ; 
 int SDMMC_BMOD_DE ; 
 int SDMMC_BMOD_FB ; 
 int SDMMC_BMOD_SWR ; 
 int /*<<< orphan*/  SDMMC_CTRL ; 
 int SDMMC_CTRL_DMA_RESET ; 
 int SDMMC_CTRL_USE_IDMAC ; 
 int /*<<< orphan*/  WRITE4 (struct dwmmc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dma_stop(struct dwmmc_softc *sc)
{
	int reg;

	reg = READ4(sc, SDMMC_CTRL);
	reg &= ~(SDMMC_CTRL_USE_IDMAC);
	reg |= (SDMMC_CTRL_DMA_RESET);
	WRITE4(sc, SDMMC_CTRL, reg);

	reg = READ4(sc, SDMMC_BMOD);
	reg &= ~(SDMMC_BMOD_DE | SDMMC_BMOD_FB);
	reg |= (SDMMC_BMOD_SWR);
	WRITE4(sc, SDMMC_BMOD, reg);

	return (0);
}