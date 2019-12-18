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
union iop3xx_desc {TYPE_4__* aau; TYPE_2__* dma; int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  u32 ;
struct iop_adma_desc_slot {int /*<<< orphan*/  hw_desc; } ;
struct iop_adma_chan {TYPE_1__* device; } ;
struct TYPE_8__ {TYPE_3__* src_edc; int /*<<< orphan*/ * src; } ;
struct TYPE_7__ {int /*<<< orphan*/  src_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  src_addr; } ;
struct TYPE_5__ {int id; } ;

/* Variables and functions */
#define  AAU_ID 130 
 int /*<<< orphan*/  BUG () ; 
#define  DMA0_ID 129 
#define  DMA1_ID 128 
 size_t __desc_idx (int) ; 

__attribute__((used)) static inline u32 iop_desc_get_src_addr(struct iop_adma_desc_slot *desc,
					struct iop_adma_chan *chan,
					int src_idx)
{
	union iop3xx_desc hw_desc = { .ptr = desc->hw_desc, };

	switch (chan->device->id) {
	case DMA0_ID:
	case DMA1_ID:
		return hw_desc.dma->src_addr;
	case AAU_ID:
		break;
	default:
		BUG();
	}

	if (src_idx < 4)
		return hw_desc.aau->src[src_idx];
	else
		return hw_desc.aau->src_edc[__desc_idx(src_idx)].src_addr;
}