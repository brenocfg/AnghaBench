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
struct bcm_dma_softc {TYPE_1__* sc_dma_ch; } ;
struct bcm_dma_cb {int /*<<< orphan*/  info; } ;
struct TYPE_2__ {int flags; void (* intr_func ) (int,void*) ;struct bcm_dma_cb* cb; void* intr_arg; } ;

/* Variables and functions */
 int BCM_DMA_CH_MAX ; 
 int BCM_DMA_CH_USED ; 
 int /*<<< orphan*/  INFO_INT_EN ; 
 struct bcm_dma_softc* bcm_dma_sc ; 

int
bcm_dma_setup_intr(int ch, void (*func)(int, void *), void *arg)
{
	struct bcm_dma_softc *sc = bcm_dma_sc;
	struct bcm_dma_cb *cb;

	if (ch < 0 || ch >= BCM_DMA_CH_MAX)
		return (-1);

	if (!(sc->sc_dma_ch[ch].flags & BCM_DMA_CH_USED))
		return (-1);

	sc->sc_dma_ch[ch].intr_func = func;
	sc->sc_dma_ch[ch].intr_arg = arg;
	cb = sc->sc_dma_ch[ch].cb;
	cb->info |= INFO_INT_EN;

	return (0);
}