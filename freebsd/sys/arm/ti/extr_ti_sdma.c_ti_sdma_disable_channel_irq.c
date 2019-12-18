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
struct ti_sdma_softc {int sc_active_channels; TYPE_1__* sc_channel; } ;
struct TYPE_2__ {int reg_cicr; int need_reg_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA4_CICR (unsigned int) ; 
 int /*<<< orphan*/  DMA4_IRQENABLE_L (unsigned int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int NUM_DMA_IRQS ; 
 int /*<<< orphan*/  TI_SDMA_LOCK (struct ti_sdma_softc*) ; 
 int /*<<< orphan*/  TI_SDMA_UNLOCK (struct ti_sdma_softc*) ; 
 int ti_sdma_read_4 (struct ti_sdma_softc*,int /*<<< orphan*/ ) ; 
 struct ti_sdma_softc* ti_sdma_sc ; 
 int /*<<< orphan*/  ti_sdma_write_4 (struct ti_sdma_softc*,int /*<<< orphan*/ ,int) ; 

int
ti_sdma_disable_channel_irq(unsigned int ch)
{
	struct ti_sdma_softc *sc = ti_sdma_sc;
	uint32_t irq_enable;
	unsigned int j;

	/* Sanity check */
	if (sc == NULL)
		return (ENOMEM);

	TI_SDMA_LOCK(sc);

	if ((sc->sc_active_channels & (1 << ch)) == 0) {
		TI_SDMA_UNLOCK(sc);
		return (EINVAL);
	}

	/* Disable all the individual error conditions */
	sc->sc_channel[ch].reg_cicr = 0x0000;
	ti_sdma_write_4(sc, DMA4_CICR(ch), 0x0000);

	/* Disable the channel interrupt enable */
	for (j = 0; j < NUM_DMA_IRQS; j++) {
		irq_enable = ti_sdma_read_4(sc, DMA4_IRQENABLE_L(j));
		irq_enable &= ~(1 << ch);

		ti_sdma_write_4(sc, DMA4_IRQENABLE_L(j), irq_enable);
	}

	/* Indicate the registers need to be rewritten on the next transaction */
	sc->sc_channel[ch].need_reg_write = 1;

	TI_SDMA_UNLOCK(sc);

	return (0);
}