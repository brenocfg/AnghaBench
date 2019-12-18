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
struct device {int dummy; } ;
struct cppi41_dd {int /*<<< orphan*/  scratch_phys; int /*<<< orphan*/  qmgr_scratch; scalar_t__ qmgr_mem; } ;

/* Variables and functions */
 scalar_t__ QMGR_LRAM0_BASE ; 
 int /*<<< orphan*/  QMGR_SCRATCH_SIZE ; 
 int /*<<< orphan*/  cppi_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  disable_sched (struct cppi41_dd*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  purge_descs (struct device*,struct cppi41_dd*) ; 

__attribute__((used)) static void deinit_cppi41(struct device *dev, struct cppi41_dd *cdd)
{
	disable_sched(cdd);

	purge_descs(dev, cdd);

	cppi_writel(0, cdd->qmgr_mem + QMGR_LRAM0_BASE);
	cppi_writel(0, cdd->qmgr_mem + QMGR_LRAM0_BASE);
	dma_free_coherent(dev, QMGR_SCRATCH_SIZE, cdd->qmgr_scratch,
			cdd->scratch_phys);
}