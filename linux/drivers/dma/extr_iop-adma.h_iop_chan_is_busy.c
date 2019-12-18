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
typedef  int u32 ;
struct iop_adma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CSR (struct iop_adma_chan*) ; 
 int IOP_ADMA_STATUS_BUSY ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int iop_chan_is_busy(struct iop_adma_chan *chan)
{
	u32 status = __raw_readl(DMA_CSR(chan));
	return (status & IOP_ADMA_STATUS_BUSY) ? 1 : 0;
}