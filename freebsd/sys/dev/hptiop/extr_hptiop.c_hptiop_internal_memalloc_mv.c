#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hpt_iop_hba {scalar_t__ ctlcfg_dmat; int /*<<< orphan*/  ctlcfg_dmamap; int /*<<< orphan*/  ctlcfg_ptr; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  parent_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  MVIOP_IOCTLCFG_SIZE ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 scalar_t__ bus_dmamap_load (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hpt_iop_hba*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (scalar_t__,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hptiop_mv_map_ctlcfg ; 

__attribute__((used)) static int hptiop_internal_memalloc_mv(struct hpt_iop_hba *hba)
{
	if (bus_dma_tag_create(hba->parent_dmat,
				1,
				0,
				BUS_SPACE_MAXADDR_32BIT,
				BUS_SPACE_MAXADDR,
				NULL, NULL,
				0x800 - 0x8,
				1,
				BUS_SPACE_MAXSIZE_32BIT,
				BUS_DMA_ALLOCNOW,
				NULL,
				NULL,
				&hba->ctlcfg_dmat)) {
		device_printf(hba->pcidev, "alloc ctlcfg_dmat failed\n");
		return -1;
	}

	if (bus_dmamem_alloc(hba->ctlcfg_dmat, (void **)&hba->ctlcfg_ptr,
		BUS_DMA_WAITOK | BUS_DMA_COHERENT,
		&hba->ctlcfg_dmamap) != 0) {
			device_printf(hba->pcidev,
					"bus_dmamem_alloc failed!\n");
			bus_dma_tag_destroy(hba->ctlcfg_dmat);
			return -1;
	}

	if (bus_dmamap_load(hba->ctlcfg_dmat,
			hba->ctlcfg_dmamap, hba->ctlcfg_ptr,
			MVIOP_IOCTLCFG_SIZE,
			hptiop_mv_map_ctlcfg, hba, 0)) {
		device_printf(hba->pcidev, "bus_dmamap_load failed!\n");
		if (hba->ctlcfg_dmat) {
			bus_dmamem_free(hba->ctlcfg_dmat,
				hba->ctlcfg_ptr, hba->ctlcfg_dmamap);
			bus_dma_tag_destroy(hba->ctlcfg_dmat);
		}
		return -1;
	}

	return 0;
}