#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int addr; } ;
struct TYPE_7__ {int addr; } ;
struct pl08x_lli_build_data {int lli_bus; int remainder; TYPE_4__ dstbus; TYPE_3__ srcbus; TYPE_1__* txd; } ;
struct pl08x_driver_data {int lli_words; TYPE_2__* vd; } ;
typedef  int dma_addr_t ;
struct TYPE_6__ {scalar_t__ ftdmac020; scalar_t__ pl080s; } ;
struct TYPE_5__ {int* llis_va; int llis_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_NUM_TSFR_LLIS ; 
 size_t PL080S_LLI_CCTL2 ; 
 int PL080_CONTROL_DST_INCR ; 
 int PL080_CONTROL_SRC_INCR ; 
 size_t PL080_LLI_CCTL ; 
 size_t PL080_LLI_DST ; 
 size_t PL080_LLI_LLI ; 
 size_t PL080_LLI_SRC ; 

__attribute__((used)) static void pl08x_fill_lli_for_desc(struct pl08x_driver_data *pl08x,
				    struct pl08x_lli_build_data *bd,
				    int num_llis, int len, u32 cctl, u32 cctl2)
{
	u32 offset = num_llis * pl08x->lli_words;
	u32 *llis_va = bd->txd->llis_va + offset;
	dma_addr_t llis_bus = bd->txd->llis_bus;

	BUG_ON(num_llis >= MAX_NUM_TSFR_LLIS);

	/* Advance the offset to next LLI. */
	offset += pl08x->lli_words;

	llis_va[PL080_LLI_SRC] = bd->srcbus.addr;
	llis_va[PL080_LLI_DST] = bd->dstbus.addr;
	llis_va[PL080_LLI_LLI] = (llis_bus + sizeof(u32) * offset);
	llis_va[PL080_LLI_LLI] |= bd->lli_bus;
	llis_va[PL080_LLI_CCTL] = cctl;
	if (pl08x->vd->pl080s)
		llis_va[PL080S_LLI_CCTL2] = cctl2;

	if (pl08x->vd->ftdmac020) {
		/* FIXME: only memcpy so far so both increase */
		bd->srcbus.addr += len;
		bd->dstbus.addr += len;
	} else {
		if (cctl & PL080_CONTROL_SRC_INCR)
			bd->srcbus.addr += len;
		if (cctl & PL080_CONTROL_DST_INCR)
			bd->dstbus.addr += len;
	}

	BUG_ON(bd->remainder < len);

	bd->remainder -= len;
}