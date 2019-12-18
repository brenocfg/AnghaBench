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
struct TYPE_6__ {int /*<<< orphan*/ * src; int /*<<< orphan*/  dest_addr; int /*<<< orphan*/  byte_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  src_addr; int /*<<< orphan*/  dest_addr; int /*<<< orphan*/  byte_count; } ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
#define  AAU_ID 130 
 int /*<<< orphan*/  BUG () ; 
#define  DMA0_ID 129 
#define  DMA1_ID 128 
 int /*<<< orphan*/  iop_desc_init_memcpy (struct iop_adma_desc_slot*,int) ; 
 int /*<<< orphan*/  iop_desc_init_null_xor (struct iop_adma_desc_slot*,int,int) ; 

__attribute__((used)) static inline void
iop_desc_init_interrupt(struct iop_adma_desc_slot *desc,
			struct iop_adma_chan *chan)
{
	union iop3xx_desc hw_desc = { .ptr = desc->hw_desc, };

	switch (chan->device->id) {
	case DMA0_ID:
	case DMA1_ID:
		iop_desc_init_memcpy(desc, 1);
		hw_desc.dma->byte_count = 0;
		hw_desc.dma->dest_addr = 0;
		hw_desc.dma->src_addr = 0;
		break;
	case AAU_ID:
		iop_desc_init_null_xor(desc, 2, 1);
		hw_desc.aau->byte_count = 0;
		hw_desc.aau->dest_addr = 0;
		hw_desc.aau->src[0] = 0;
		hw_desc.aau->src[1] = 0;
		break;
	default:
		BUG();
	}
}