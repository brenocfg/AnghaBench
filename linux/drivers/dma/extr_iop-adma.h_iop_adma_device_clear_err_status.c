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
typedef  int u32 ;
struct iop_adma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
#define  AAU_ID 130 
 int /*<<< orphan*/  BUG () ; 
#define  DMA0_ID 129 
#define  DMA1_ID 128 
 int /*<<< orphan*/  DMA_CSR (struct iop_adma_chan*) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iop_adma_device_clear_err_status(struct iop_adma_chan *chan)
{
	u32 status = __raw_readl(DMA_CSR(chan));

	switch (chan->device->id) {
	case DMA0_ID:
	case DMA1_ID:
		status &= (1 << 5) | (1 << 3) | (1 << 2) | (1 << 1);
		break;
	case AAU_ID:
		status &= (1 << 5);
		break;
	default:
		BUG();
	}

	__raw_writel(status, DMA_CSR(chan));
}