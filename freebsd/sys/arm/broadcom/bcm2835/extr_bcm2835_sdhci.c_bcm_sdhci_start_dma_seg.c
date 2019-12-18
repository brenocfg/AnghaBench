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
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct sdhci_slot {int offset; int intmask; TYPE_2__* curcmd; } ;
struct bcm_sdhci_softc {int* dmamap_seg_sizes; int /*<<< orphan*/  sc_dma_ch; struct sdhci_slot sc_slot; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_dma_map; int /*<<< orphan*/  sc_dma_tag; int /*<<< orphan*/  sc_sdhci_buffer_phys; int /*<<< orphan*/ * dmamap_seg_addrs; int /*<<< orphan*/  dmamap_seg_index; } ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int BCM_DMA_128BIT ; 
 int BCM_DMA_32BIT ; 
 int /*<<< orphan*/  BCM_DMA_DREQ_EMMC ; 
 int /*<<< orphan*/  BCM_DMA_DREQ_NONE ; 
 int /*<<< orphan*/  BCM_DMA_INC_ADDR ; 
 int /*<<< orphan*/  BCM_DMA_SAME_ADDR ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MMC_DATA_READ ; 
 int SDHCI_INT_DATA_AVAIL ; 
 int SDHCI_INT_DATA_END ; 
 int SDHCI_INT_SPACE_AVAIL ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  bcm_dma_setup_dst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm_dma_setup_src (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bcm_dma_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm_sdhci_write_4 (int /*<<< orphan*/ ,struct sdhci_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bcm_sdhci_start_dma_seg(struct bcm_sdhci_softc *sc)
{
	struct sdhci_slot *slot;
	vm_paddr_t pdst, psrc;
	int err, idx, len, sync_op, width;

	slot = &sc->sc_slot;
	idx = sc->dmamap_seg_index++;
	len = sc->dmamap_seg_sizes[idx];
	slot->offset += len;
	width = (len & 0xf ? BCM_DMA_32BIT : BCM_DMA_128BIT);

	if (slot->curcmd->data->flags & MMC_DATA_READ) {
		bcm_dma_setup_src(sc->sc_dma_ch, BCM_DMA_DREQ_EMMC,
		    BCM_DMA_SAME_ADDR, BCM_DMA_32BIT); 
		bcm_dma_setup_dst(sc->sc_dma_ch, BCM_DMA_DREQ_NONE,
		    BCM_DMA_INC_ADDR, width);
		psrc = sc->sc_sdhci_buffer_phys;
		pdst = sc->dmamap_seg_addrs[idx];
		sync_op = BUS_DMASYNC_PREREAD;
	} else {
		bcm_dma_setup_src(sc->sc_dma_ch, BCM_DMA_DREQ_NONE,
		    BCM_DMA_INC_ADDR, width);
		bcm_dma_setup_dst(sc->sc_dma_ch, BCM_DMA_DREQ_EMMC,
		    BCM_DMA_SAME_ADDR, BCM_DMA_32BIT);
		psrc = sc->dmamap_seg_addrs[idx];
		pdst = sc->sc_sdhci_buffer_phys;
		sync_op = BUS_DMASYNC_PREWRITE;
	}

	/*
	 * When starting a new DMA operation do the busdma sync operation, and
	 * disable SDCHI data interrrupts because we'll be driven by DMA
	 * interrupts (or SDHCI error interrupts) until the IO is done.
	 */
	if (idx == 0) {
		bus_dmamap_sync(sc->sc_dma_tag, sc->sc_dma_map, sync_op);
		slot->intmask &= ~(SDHCI_INT_DATA_AVAIL | 
		    SDHCI_INT_SPACE_AVAIL | SDHCI_INT_DATA_END);
		bcm_sdhci_write_4(sc->sc_dev, &sc->sc_slot, SDHCI_SIGNAL_ENABLE,
		    slot->intmask);
	}

	/*
	 * Start the DMA transfer.  Only programming errors (like failing to
	 * allocate a channel) cause a non-zero return from bcm_dma_start().
	 */
	err = bcm_dma_start(sc->sc_dma_ch, psrc, pdst, len);
	KASSERT((err == 0), ("bcm2835_sdhci: failed DMA start"));
}