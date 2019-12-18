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
struct bcm_dma_softc {TYPE_2__* sc_dma_ch; } ;
struct TYPE_4__ {int flags; TYPE_1__* cb; } ;
struct TYPE_3__ {int info; } ;

/* Variables and functions */
 int BCM_DMA_128BIT ; 
 int BCM_DMA_CH_MAX ; 
 int BCM_DMA_CH_USED ; 
 int BCM_DMA_INC_ADDR ; 
 int INFO_PERMAP_MASK ; 
 int INFO_PERMAP_SHIFT ; 
 int INFO_S_DREQ ; 
 int INFO_S_INC ; 
 int INFO_S_WIDTH ; 
 struct bcm_dma_softc* bcm_dma_sc ; 

int
bcm_dma_setup_src(int ch, int dreq, int inc_addr, int width)
{
	struct bcm_dma_softc *sc = bcm_dma_sc;
	uint32_t info;

	if (ch < 0 || ch >= BCM_DMA_CH_MAX)
		return (-1);

	if (!(sc->sc_dma_ch[ch].flags & BCM_DMA_CH_USED))
		return (-1);

	info = sc->sc_dma_ch[ch].cb->info;
	info &= ~INFO_PERMAP_MASK;
	info |= (dreq << INFO_PERMAP_SHIFT) & INFO_PERMAP_MASK;

	if (dreq)
		info |= INFO_S_DREQ;
	else
		info &= ~INFO_S_DREQ;

	if (width == BCM_DMA_128BIT)
		info |= INFO_S_WIDTH;
	else
		info &= ~INFO_S_WIDTH;

	if (inc_addr == BCM_DMA_INC_ADDR)
		info |= INFO_S_INC;
	else
		info &= ~INFO_S_INC;

	sc->sc_dma_ch[ch].cb->info = info;

	return (0);
}