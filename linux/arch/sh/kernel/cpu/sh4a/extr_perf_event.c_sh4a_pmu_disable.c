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
struct hw_perf_event {int dummy; } ;

/* Variables and functions */
 unsigned int CCBR_CIT_MASK ; 
 unsigned int CCBR_DUC ; 
 int /*<<< orphan*/  PPC_CCBR (int) ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh4a_pmu_disable(struct hw_perf_event *hwc, int idx)
{
	unsigned int tmp;

	tmp = __raw_readl(PPC_CCBR(idx));
	tmp &= ~(CCBR_CIT_MASK | CCBR_DUC);
	__raw_writel(tmp, PPC_CCBR(idx));
}