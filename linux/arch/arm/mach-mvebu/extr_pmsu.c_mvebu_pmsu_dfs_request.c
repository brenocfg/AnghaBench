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

/* Variables and functions */
 int ETIME ; 
 unsigned long HZ ; 
 scalar_t__ PMSU_EVENT_STATUS_AND_MASK (int) ; 
 int PMSU_EVENT_STATUS_AND_MASK_DFS_DONE ; 
 int PMSU_EVENT_STATUS_AND_MASK_DFS_DONE_MASK ; 
 int cpu_logical_map (int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mvebu_pmsu_dfs_request_local ; 
 scalar_t__ pmsu_mp_base ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int mvebu_pmsu_dfs_request(int cpu)
{
	unsigned long timeout;
	int hwcpu = cpu_logical_map(cpu);
	u32 reg;

	/* Clear any previous DFS DONE event */
	reg = readl(pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));
	reg &= ~PMSU_EVENT_STATUS_AND_MASK_DFS_DONE;
	writel(reg, pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));

	/* Mask the DFS done interrupt, since we are going to poll */
	reg = readl(pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));
	reg |= PMSU_EVENT_STATUS_AND_MASK_DFS_DONE_MASK;
	writel(reg, pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));

	/* Trigger the DFS on the appropriate CPU */
	smp_call_function_single(cpu, mvebu_pmsu_dfs_request_local,
				 NULL, false);

	/* Poll until the DFS done event is generated */
	timeout = jiffies + HZ;
	while (time_before(jiffies, timeout)) {
		reg = readl(pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));
		if (reg & PMSU_EVENT_STATUS_AND_MASK_DFS_DONE)
			break;
		udelay(10);
	}

	if (time_after(jiffies, timeout))
		return -ETIME;

	/* Restore the DFS mask to its original state */
	reg = readl(pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));
	reg &= ~PMSU_EVENT_STATUS_AND_MASK_DFS_DONE_MASK;
	writel(reg, pmsu_mp_base + PMSU_EVENT_STATUS_AND_MASK(hwcpu));

	return 0;
}