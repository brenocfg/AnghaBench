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
typedef  int /*<<< orphan*/  u32 ;
struct iop_adma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAU_ADAR (struct iop_adma_chan*) ; 
#define  AAU_ID 130 
 int /*<<< orphan*/  BUG () ; 
#define  DMA0_ID 129 
#define  DMA1_ID 128 
 int /*<<< orphan*/  DMA_DAR (struct iop_adma_chan*) ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 iop_chan_get_current_descriptor(struct iop_adma_chan *chan)
{
	int id = chan->device->id;

	switch (id) {
	case DMA0_ID:
	case DMA1_ID:
		return __raw_readl(DMA_DAR(chan));
	case AAU_ID:
		return __raw_readl(AAU_ADAR(chan));
	default:
		BUG();
	}
	return 0;
}