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
struct iop_adma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
#define  AAU_ID 130 
 int /*<<< orphan*/  BUG () ; 
#define  DMA0_ID 129 
#define  DMA1_ID 128 
 int iop3xx_aau_xor_slot_count (int /*<<< orphan*/ ,int,int*) ; 
 int iop_chan_memcpy_slot_count (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline int
iop_chan_interrupt_slot_count(int *slots_per_op, struct iop_adma_chan *chan)
{
	switch (chan->device->id) {
	case DMA0_ID:
	case DMA1_ID:
		return iop_chan_memcpy_slot_count(0, slots_per_op);
	case AAU_ID:
		return iop3xx_aau_xor_slot_count(0, 2, slots_per_op);
	default:
		BUG();
	}
	return 0;
}