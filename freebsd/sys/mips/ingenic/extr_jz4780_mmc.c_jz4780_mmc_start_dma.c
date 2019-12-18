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
struct jz4780_mmc_softc {int /*<<< orphan*/  sc_dma_ctl; int /*<<< orphan*/  sc_dma_desc_phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_MMC_WRITE_4 (struct jz4780_mmc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_MSC_DMAC ; 
 int /*<<< orphan*/  JZ_MSC_DMANDA ; 

__attribute__((used)) static void
jz4780_mmc_start_dma(struct jz4780_mmc_softc *sc)
{

	/* Set the address of the first descriptor */
	JZ_MMC_WRITE_4(sc, JZ_MSC_DMANDA, sc->sc_dma_desc_phys);
	/* Enable and start the dma engine */
	JZ_MMC_WRITE_4(sc, JZ_MSC_DMAC, sc->sc_dma_ctl);
}