#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union iop3xx_desc {TYPE_3__* aau; TYPE_2__* dma; int /*<<< orphan*/  ptr; } ;
struct iop_adma_desc_slot {int /*<<< orphan*/  hw_desc; } ;
struct iop_adma_chan {TYPE_1__* device; } ;
typedef  void* dma_addr_t ;
struct TYPE_6__ {void* dest_addr; } ;
struct TYPE_5__ {void* dest_addr; } ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
#define  AAU_ID 130 
 int /*<<< orphan*/  BUG () ; 
#define  DMA0_ID 129 
#define  DMA1_ID 128 

__attribute__((used)) static inline void iop_desc_set_dest_addr(struct iop_adma_desc_slot *desc,
					struct iop_adma_chan *chan,
					dma_addr_t addr)
{
	union iop3xx_desc hw_desc = { .ptr = desc->hw_desc, };

	switch (chan->device->id) {
	case DMA0_ID:
	case DMA1_ID:
		hw_desc.dma->dest_addr = addr;
		break;
	case AAU_ID:
		hw_desc.aau->dest_addr = addr;
		break;
	default:
		BUG();
	}
}