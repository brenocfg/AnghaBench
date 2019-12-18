#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct jz4780_mmc_softc {int sc_dma_map_err; int /*<<< orphan*/  sc_dev; scalar_t__ sc_dma_desc_phys; struct jz4780_mmc_dma_desc* sc_dma_desc; } ;
struct jz4780_mmc_dma_desc {int dma_cmd; scalar_t__ dma_next; int /*<<< orphan*/  dma_len; int /*<<< orphan*/  dma_phys; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int JZ_DMA_ENDI ; 
 int JZ_DMA_LINK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
jz4780_mmc_dma_cb(void *arg, bus_dma_segment_t *segs, int nsegs, int err)
{
	struct jz4780_mmc_dma_desc *dma_desc;
	struct jz4780_mmc_softc *sc;
	uint32_t dma_desc_phys;
	int i;

	sc = (struct jz4780_mmc_softc *)arg;
	sc->sc_dma_map_err = err;
	dma_desc = sc->sc_dma_desc;
	dma_desc_phys = sc->sc_dma_desc_phys;

	/* Note nsegs is guaranteed to be zero if err is non-zero. */
	for (i = 0; i < nsegs; i++) {
		dma_desc[i].dma_phys = segs[i].ds_addr;
		dma_desc[i].dma_len  = segs[i].ds_len;
		if (i < (nsegs - 1)) {
			dma_desc_phys += sizeof(struct jz4780_mmc_dma_desc);
			dma_desc[i].dma_next = dma_desc_phys;
			dma_desc[i].dma_cmd = (i << 16) | JZ_DMA_LINK;
		} else {
			dma_desc[i].dma_next = 0;
			dma_desc[i].dma_cmd = (i << 16) | JZ_DMA_ENDI;
		}
#ifdef JZ_MMC_DEBUG
		device_printf(sc->sc_dev, "%d: desc %#x phys %#x len %d next %#x cmd %#x\n",
		    i, dma_desc_phys - sizeof(struct jz4780_mmc_dma_desc),
		    dma_desc[i].dma_phys, dma_desc[i].dma_len,
		    dma_desc[i].dma_next, dma_desc[i].dma_cmd);
#endif
 	}
}