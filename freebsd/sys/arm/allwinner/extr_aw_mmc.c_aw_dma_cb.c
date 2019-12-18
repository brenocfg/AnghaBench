#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct aw_mmc_softc {int aw_dma_map_err; scalar_t__ aw_dma_desc_phys; TYPE_1__* aw_mmc_conf; struct aw_mmc_dma_desc* aw_dma_desc; } ;
struct aw_mmc_dma_desc {scalar_t__ buf_size; int config; scalar_t__ next; int /*<<< orphan*/  buf_addr; } ;
struct TYPE_5__ {scalar_t__ ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_4__ {scalar_t__ dma_xferlen; } ;

/* Variables and functions */
 int AW_MMC_DMA_CONFIG_CH ; 
 int AW_MMC_DMA_CONFIG_DIC ; 
 int AW_MMC_DMA_CONFIG_ER ; 
 int AW_MMC_DMA_CONFIG_FD ; 
 int AW_MMC_DMA_CONFIG_LD ; 
 int AW_MMC_DMA_CONFIG_OWN ; 

__attribute__((used)) static void
aw_dma_cb(void *arg, bus_dma_segment_t *segs, int nsegs, int err)
{
	int i;
	struct aw_mmc_dma_desc *dma_desc;
	struct aw_mmc_softc *sc;

	sc = (struct aw_mmc_softc *)arg;
	sc->aw_dma_map_err = err;

	if (err)
		return;

	dma_desc = sc->aw_dma_desc;
	for (i = 0; i < nsegs; i++) {
		if (segs[i].ds_len == sc->aw_mmc_conf->dma_xferlen)
			dma_desc[i].buf_size = 0;		/* Size of 0 indicate max len */
		else
			dma_desc[i].buf_size = segs[i].ds_len;
		dma_desc[i].buf_addr = segs[i].ds_addr;
		dma_desc[i].config = AW_MMC_DMA_CONFIG_CH |
			AW_MMC_DMA_CONFIG_OWN | AW_MMC_DMA_CONFIG_DIC;

		dma_desc[i].next = sc->aw_dma_desc_phys +
			((i + 1) * sizeof(struct aw_mmc_dma_desc));
	}

	dma_desc[0].config |= AW_MMC_DMA_CONFIG_FD;
	dma_desc[nsegs - 1].config |= AW_MMC_DMA_CONFIG_LD |
		AW_MMC_DMA_CONFIG_ER;
	dma_desc[nsegs - 1].config &= ~AW_MMC_DMA_CONFIG_DIC;
	dma_desc[nsegs - 1].next = 0;
}