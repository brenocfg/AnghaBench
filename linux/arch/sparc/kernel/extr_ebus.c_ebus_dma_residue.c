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
struct ebus_dma_info {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ EBDMA_COUNT ; 
 unsigned int readl (scalar_t__) ; 

unsigned int ebus_dma_residue(struct ebus_dma_info *p)
{
	return readl(p->regs + EBDMA_COUNT);
}