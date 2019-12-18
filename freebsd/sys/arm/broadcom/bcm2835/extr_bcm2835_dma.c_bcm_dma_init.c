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
typedef  int uint32_t ;
struct bcm_dma_softc {int /*<<< orphan*/  sc_mem; int /*<<< orphan*/  sc_dma_tag; struct bcm_dma_ch* sc_dma_ch; } ;
struct bcm_dma_ch {int ch; TYPE_1__* cb; int /*<<< orphan*/  flags; int /*<<< orphan*/  vc_cb; int /*<<< orphan*/  dma_map; } ;
struct bcm_dma_cb {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_DMA_CH_FREE ; 
 int BCM_DMA_CH_MAX ; 
 int /*<<< orphan*/  BCM_DMA_CH_UNMAP ; 
 int /*<<< orphan*/  BCM_DMA_CS (int) ; 
 int /*<<< orphan*/  BCM_DMA_ENABLE ; 
 int /*<<< orphan*/  BCM_DMA_INT_STATUS ; 
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CS_RESET ; 
 int /*<<< orphan*/  INFO_WAIT_RESP ; 
 int bcm_dma_channel_mask ; 
 int /*<<< orphan*/  bcm_dmamap_cb ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct bcm_dma_ch*,int) ; 
 struct bcm_dma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
bcm_dma_init(device_t dev)
{
	struct bcm_dma_softc *sc = device_get_softc(dev);
	uint32_t reg;
	struct bcm_dma_ch *ch;
	void *cb_virt;
	vm_paddr_t cb_phys;
	int err;
	int i;

	/*
	 * Only channels set in bcm_dma_channel_mask can be controlled by us.
	 * The others are out of our control as well as the corresponding bits
	 * in both BCM_DMA_ENABLE and BCM_DMA_INT_STATUS global registers. As
	 * these registers are RW ones, there is no safe way how to write only
	 * the bits which can be controlled by us.
	 *
	 * Fortunately, after reset, all channels are enabled in BCM_DMA_ENABLE
	 * register and all statuses are cleared in BCM_DMA_INT_STATUS one.
	 * Not touching these registers is a trade off between correct
	 * initialization which does not count on anything and not messing up
	 * something we have no control over.
	 */
	reg = bus_read_4(sc->sc_mem, BCM_DMA_ENABLE);
	if ((reg & bcm_dma_channel_mask) != bcm_dma_channel_mask)
		device_printf(dev, "channels are not enabled\n");
	reg = bus_read_4(sc->sc_mem, BCM_DMA_INT_STATUS);
	if ((reg & bcm_dma_channel_mask) != 0)
		device_printf(dev, "statuses are not cleared\n");

	/* Allocate DMA chunks control blocks */
	/* p.40 of spec - control block should be 32-bit aligned */
	err = bus_dma_tag_create(bus_get_dma_tag(dev),
	    1, 0, BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR, NULL, NULL,
	    sizeof(struct bcm_dma_cb), 1,
	    sizeof(struct bcm_dma_cb),
	    BUS_DMA_ALLOCNOW, NULL, NULL,
	    &sc->sc_dma_tag);

	if (err) {
		device_printf(dev, "failed allocate DMA tag\n");
		return (err);
	}

	/* setup initial settings */
	for (i = 0; i < BCM_DMA_CH_MAX; i++) {
		ch = &sc->sc_dma_ch[i];

		bzero(ch, sizeof(struct bcm_dma_ch));
		ch->ch = i;
		ch->flags = BCM_DMA_CH_UNMAP;

		if ((bcm_dma_channel_mask & (1 << i)) == 0)
			continue;

		err = bus_dmamem_alloc(sc->sc_dma_tag, &cb_virt,
		    BUS_DMA_WAITOK | BUS_DMA_COHERENT | BUS_DMA_ZERO,
		    &ch->dma_map);
		if (err) {
			device_printf(dev, "cannot allocate DMA memory\n");
			break;
		}

		/* 
		 * Least alignment for busdma-allocated stuff is cache 
		 * line size, so just make sure nothing stupid happened
		 * and we got properly aligned address
		 */
		if ((uintptr_t)cb_virt & 0x1f) {
			device_printf(dev,
			    "DMA address is not 32-bytes aligned: %p\n",
			    (void*)cb_virt);
			break;
		}

		err = bus_dmamap_load(sc->sc_dma_tag, ch->dma_map, cb_virt,
		    sizeof(struct bcm_dma_cb), bcm_dmamap_cb, &cb_phys,
		    BUS_DMA_WAITOK);
		if (err) {
			device_printf(dev, "cannot load DMA memory\n");
			break;
		}

		ch->cb = cb_virt;
		ch->vc_cb = cb_phys;
		ch->flags = BCM_DMA_CH_FREE;
		ch->cb->info = INFO_WAIT_RESP;

		/* reset DMA engine */
		bus_write_4(sc->sc_mem, BCM_DMA_CS(i), CS_RESET);
	}

	return (0);
}