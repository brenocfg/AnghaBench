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
struct omap_type2_desc {int next_desc; int fn; int /*<<< orphan*/  en; int /*<<< orphan*/  csfi; int /*<<< orphan*/  cdfi; int /*<<< orphan*/  csei; int /*<<< orphan*/  cdei; int /*<<< orphan*/  cicr; int /*<<< orphan*/  addr; } ;
struct omap_sg {int t2_desc_paddr; int fn; int /*<<< orphan*/  fi; int /*<<< orphan*/  ei; int /*<<< orphan*/  addr; int /*<<< orphan*/  en; struct omap_type2_desc* t2_desc; } ;
struct omap_desc {int /*<<< orphan*/  fi; int /*<<< orphan*/  ei; int /*<<< orphan*/  cicr; struct omap_sg* sg; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 int /*<<< orphan*/  CICR_BLOCK_IE ; 
 int /*<<< orphan*/  DESC_NTYPE_TYPE2 ; 
 int /*<<< orphan*/  DESC_NXT_DV_REFRESH ; 
 int /*<<< orphan*/  DESC_NXT_DV_REUSE ; 
 int /*<<< orphan*/  DESC_NXT_SV_REFRESH ; 
 int /*<<< orphan*/  DESC_NXT_SV_REUSE ; 
#define  DMA_DEV_TO_MEM 129 
#define  DMA_MEM_TO_DEV 128 

__attribute__((used)) static void omap_dma_fill_type2_desc(struct omap_desc *d, int idx,
				     enum dma_transfer_direction dir, bool last)
{
	struct omap_sg *sg = &d->sg[idx];
	struct omap_type2_desc *t2_desc = sg->t2_desc;

	if (idx)
		d->sg[idx - 1].t2_desc->next_desc = sg->t2_desc_paddr;
	if (last)
		t2_desc->next_desc = 0xfffffffc;

	t2_desc->en = sg->en;
	t2_desc->addr = sg->addr;
	t2_desc->fn = sg->fn & 0xffff;
	t2_desc->cicr = d->cicr;
	if (!last)
		t2_desc->cicr &= ~CICR_BLOCK_IE;

	switch (dir) {
	case DMA_DEV_TO_MEM:
		t2_desc->cdei = sg->ei;
		t2_desc->csei = d->ei;
		t2_desc->cdfi = sg->fi;
		t2_desc->csfi = d->fi;

		t2_desc->en |= DESC_NXT_DV_REFRESH;
		t2_desc->en |= DESC_NXT_SV_REUSE;
		break;
	case DMA_MEM_TO_DEV:
		t2_desc->cdei = d->ei;
		t2_desc->csei = sg->ei;
		t2_desc->cdfi = d->fi;
		t2_desc->csfi = sg->fi;

		t2_desc->en |= DESC_NXT_SV_REFRESH;
		t2_desc->en |= DESC_NXT_DV_REUSE;
		break;
	default:
		return;
	}

	t2_desc->en |= DESC_NTYPE_TYPE2;
}