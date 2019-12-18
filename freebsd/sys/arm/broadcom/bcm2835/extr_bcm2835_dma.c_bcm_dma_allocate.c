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
struct bcm_dma_softc {int /*<<< orphan*/  sc_mtx; TYPE_1__* sc_dma_ch; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int BCM_DMA_CH_FREE ; 
 int BCM_DMA_CH_INVALID ; 
 int BCM_DMA_CH_MAX ; 
 int BCM_DMA_CH_USED ; 
 struct bcm_dma_softc* bcm_dma_sc ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
bcm_dma_allocate(int req_ch)
{
	struct bcm_dma_softc *sc = bcm_dma_sc;
	int ch = BCM_DMA_CH_INVALID;
	int i;

	if (req_ch >= BCM_DMA_CH_MAX)
		return (BCM_DMA_CH_INVALID);

	/* Auto(req_ch < 0) or CH specified */
	mtx_lock(&sc->sc_mtx);

	if (req_ch < 0) {
		for (i = 0; i < BCM_DMA_CH_MAX; i++) {
			if (sc->sc_dma_ch[i].flags & BCM_DMA_CH_FREE) {
				ch = i;
				sc->sc_dma_ch[ch].flags &= ~BCM_DMA_CH_FREE;
				sc->sc_dma_ch[ch].flags |= BCM_DMA_CH_USED;
				break;
			}
		}
	}
	else {
		if (sc->sc_dma_ch[req_ch].flags & BCM_DMA_CH_FREE) {
			ch = req_ch;
			sc->sc_dma_ch[ch].flags &= ~BCM_DMA_CH_FREE;
			sc->sc_dma_ch[ch].flags |= BCM_DMA_CH_USED;
		}
	}

	mtx_unlock(&sc->sc_mtx);
	return (ch);
}