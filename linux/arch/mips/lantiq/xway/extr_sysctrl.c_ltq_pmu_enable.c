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

/* Variables and functions */
 int /*<<< orphan*/  PMU_PWDCR ; 
 int /*<<< orphan*/  PMU_PWDSR ; 
 int /*<<< orphan*/  g_pmu_lock ; 
 int /*<<< orphan*/  panic (char*) ; 
 unsigned int pmu_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_w32 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ltq_pmu_enable(unsigned int module)
{
	int retry = 1000000;

	spin_lock(&g_pmu_lock);
	pmu_w32(pmu_r32(PMU_PWDCR) & ~module, PMU_PWDCR);
	do {} while (--retry && (pmu_r32(PMU_PWDSR) & module));
	spin_unlock(&g_pmu_lock);

	if (!retry)
		panic("activating PMU module failed!");
}