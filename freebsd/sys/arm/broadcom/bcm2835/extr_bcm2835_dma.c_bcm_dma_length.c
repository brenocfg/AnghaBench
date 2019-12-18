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
typedef  int /*<<< orphan*/  uint32_t ;
struct bcm_dma_softc {TYPE_1__* sc_dma_ch; } ;
struct bcm_dma_cb {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int flags; struct bcm_dma_cb* cb; } ;

/* Variables and functions */
 int BCM_DMA_CH_MAX ; 
 int BCM_DMA_CH_USED ; 
 struct bcm_dma_softc* bcm_dma_sc ; 

uint32_t
bcm_dma_length(int ch)
{
	struct bcm_dma_softc *sc = bcm_dma_sc;
	struct bcm_dma_cb *cb;

	if (ch < 0 || ch >= BCM_DMA_CH_MAX)
		return (0);

	if (!(sc->sc_dma_ch[ch].flags & BCM_DMA_CH_USED))
		return (0);

	cb = sc->sc_dma_ch[ch].cb;

	return (cb->len);
}