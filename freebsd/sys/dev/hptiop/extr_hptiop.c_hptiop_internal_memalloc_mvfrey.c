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
typedef  int u_int32_t ;
struct mvfrey_outlist_entry {int dummy; } ;
struct mvfrey_inlist_entry {int dummy; } ;
struct TYPE_3__ {int list_count; int internal_mem_size; } ;
struct TYPE_4__ {TYPE_1__ mvfrey; } ;
struct hpt_iop_hba {scalar_t__ ctlcfg_dmat; int /*<<< orphan*/  ctlcfg_dmamap; int /*<<< orphan*/  ctlcfg_ptr; int /*<<< orphan*/  pcidev; TYPE_2__ u; int /*<<< orphan*/  parent_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_WAITOK ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int BUS_SPACE_RD4_MVFREY2 (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 scalar_t__ bus_dmamap_load (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct hpt_iop_hba*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (scalar_t__,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hptiop_mvfrey_map_ctlcfg ; 
 int /*<<< orphan*/  inbound_conf_ctl ; 

__attribute__((used)) static int hptiop_internal_memalloc_mvfrey(struct hpt_iop_hba *hba)
{
	u_int32_t list_count = BUS_SPACE_RD4_MVFREY2(inbound_conf_ctl);

	list_count >>= 16;

	if (list_count == 0) {
		return -1;
	}

	hba->u.mvfrey.list_count = list_count;
	hba->u.mvfrey.internal_mem_size = 0x800
							+ list_count * sizeof(struct mvfrey_inlist_entry)
							+ list_count * sizeof(struct mvfrey_outlist_entry)
							+ sizeof(int);
	if (bus_dma_tag_create(hba->parent_dmat,
				1,
				0,
				BUS_SPACE_MAXADDR_32BIT,
				BUS_SPACE_MAXADDR,
				NULL, NULL,
				hba->u.mvfrey.internal_mem_size,
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
			hba->u.mvfrey.internal_mem_size,
			hptiop_mvfrey_map_ctlcfg, hba, 0)) {
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