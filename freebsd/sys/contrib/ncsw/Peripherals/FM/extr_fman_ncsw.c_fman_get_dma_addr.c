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
typedef  int uint64_t ;
struct fman_dma_regs {int /*<<< orphan*/  fmdmtah; int /*<<< orphan*/  fmdmtal; } ;

/* Variables and functions */
 scalar_t__ ioread32be (int /*<<< orphan*/ *) ; 

uint64_t fman_get_dma_addr(struct fman_dma_regs *dma_rg)
{
	uint64_t addr;

	addr = (uint64_t)ioread32be(&dma_rg->fmdmtal);
	addr |= ((uint64_t)(ioread32be(&dma_rg->fmdmtah)) << 32);

	return addr;
}