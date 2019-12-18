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
struct bcm_dma_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; TYPE_1__* sc_dma_ch; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/ * intr_arg; int /*<<< orphan*/ * intr_func; } ;

/* Variables and functions */
 int BCM_DMA_CH_FREE ; 
 int BCM_DMA_CH_MAX ; 
 int BCM_DMA_CH_USED ; 
 int /*<<< orphan*/  bcm_dma_reset (int /*<<< orphan*/ ,int) ; 
 struct bcm_dma_softc* bcm_dma_sc ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
bcm_dma_free(int ch)
{
	struct bcm_dma_softc *sc = bcm_dma_sc;

	if (ch < 0 || ch >= BCM_DMA_CH_MAX)
		return (-1);

	mtx_lock(&sc->sc_mtx);
	if (sc->sc_dma_ch[ch].flags & BCM_DMA_CH_USED) {
		sc->sc_dma_ch[ch].flags |= BCM_DMA_CH_FREE;
		sc->sc_dma_ch[ch].flags &= ~BCM_DMA_CH_USED;
		sc->sc_dma_ch[ch].intr_func = NULL;
		sc->sc_dma_ch[ch].intr_arg = NULL;

		/* reset DMA engine */
		bcm_dma_reset(sc->sc_dev, ch);
	}

	mtx_unlock(&sc->sc_mtx);
	return (0);
}