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
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct bcm_dma_softc {TYPE_1__* sc_dma_ch; int /*<<< orphan*/  sc_mem; int /*<<< orphan*/  sc_dma_tag; } ;
struct bcm_dma_cb {int len; void* dst; void* src; } ;
struct TYPE_2__ {int flags; struct bcm_dma_cb* cb; int /*<<< orphan*/  vc_cb; int /*<<< orphan*/  dma_map; } ;

/* Variables and functions */
 scalar_t__ BCM2835_ARM_IS_IO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_DMA_CBADDR (int) ; 
 int BCM_DMA_CH_MAX ; 
 int BCM_DMA_CH_USED ; 
 int /*<<< orphan*/  BCM_DMA_CS (int) ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CS_ACTIVE ; 
 void* IO_TO_VCBUS (int /*<<< orphan*/ ) ; 
 void* PHYS_TO_VCBUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_dma_cb_dump (struct bcm_dma_cb*) ; 
 int /*<<< orphan*/  bcm_dma_reg_dump (int) ; 
 struct bcm_dma_softc* bcm_dma_sc ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bcm_dma_start(int ch, vm_paddr_t src, vm_paddr_t dst, int len)
{
	struct bcm_dma_softc *sc = bcm_dma_sc;
	struct bcm_dma_cb *cb;

	if (ch < 0 || ch >= BCM_DMA_CH_MAX)
		return (-1);

	if (!(sc->sc_dma_ch[ch].flags & BCM_DMA_CH_USED))
		return (-1);

	cb = sc->sc_dma_ch[ch].cb;
	if (BCM2835_ARM_IS_IO(src))
		cb->src = IO_TO_VCBUS(src);
	else
		cb->src = PHYS_TO_VCBUS(src);
	if (BCM2835_ARM_IS_IO(dst))
		cb->dst = IO_TO_VCBUS(dst);
	else
		cb->dst = PHYS_TO_VCBUS(dst);
	cb->len = len;

	bus_dmamap_sync(sc->sc_dma_tag,
	    sc->sc_dma_ch[ch].dma_map, BUS_DMASYNC_PREWRITE);

	bus_write_4(sc->sc_mem, BCM_DMA_CBADDR(ch),
	    sc->sc_dma_ch[ch].vc_cb);
	bus_write_4(sc->sc_mem, BCM_DMA_CS(ch), CS_ACTIVE);

#ifdef DEBUG
	bcm_dma_cb_dump(sc->sc_dma_ch[ch].cb);
	bcm_dma_reg_dump(ch);
#endif

	return (0);
}