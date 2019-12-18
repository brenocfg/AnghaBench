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
 int DMA4_CICR_MISALIGNED_ADRS_ERR_IE ; 
 int DMA4_CICR_SECURE_ERR_IE ; 
 int DMA4_CICR_SUPERVISOR_ERR_IE ; 
 int DMA4_CICR_TRANS_ERR_IE ; 
 int /*<<< orphan*/  DMA4_IRQENABLE_L (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TI_SDMA_LOCK (struct ti_sdma_softc*) ; 
 int /*<<< orphan*/  TI_SDMA_UNLOCK (struct ti_sdma_softc*) ; 
 int ti_sdma_read_4 (struct ti_sdma_softc*,int /*<<< orphan*/ ) ; 
 struct ti_sdma_softc* ti_sdma_sc ; 
 int /*<<< orphan*/  ti_sdma_write_4 (struct ti_sdma_softc*,int /*<<< orphan*/ ,int) ; 

int
ti_sdma_enable_channel_irq(unsigned int ch, uint32_t flags)
{
	struct ti_sdma_softc *sc = ti_sdma_sc;
	uint32_t irq_enable;

	/* Sanity check */
	if (sc == NULL)
		return (ENOMEM);

	TI_SDMA_LOCK(sc);

	if ((sc->sc_active_channels & (1 << ch)) == 0) {
		TI_SDMA_UNLOCK(sc);
		return (EINVAL);
	}

	/* Always enable the error interrupts if we have interrupts enabled */
	flags |= DMA4_CICR_TRANS_ERR_IE | DMA4_CICR_SECURE_ERR_IE |
	         DMA4_CICR_SUPERVISOR_ERR_IE | DMA4_CICR_MISALIGNED_ADRS_ERR_IE;

	sc->sc_channel[ch].reg_cicr = flags;

	/* Write the values to the register */
	ti_sdma_write_4(sc, DMA4_CICR(ch), flags);

	/* Enable the channel interrupt enable */
	irq_enable = ti_sdma_read_4(sc, DMA4_IRQENABLE_L(0));
	irq_enable |= (1 << ch);

	ti_sdma_write_4(sc, DMA4_IRQENABLE_L(0), irq_enable);

	/* Indicate the registers need to be rewritten on the next transaction */
	sc->sc_channel[ch].need_reg_write = 1;

	TI_SDMA_UNLOCK(sc);

	return (0);
}