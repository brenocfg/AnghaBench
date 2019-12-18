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
typedef  int u64 ;

/* Variables and functions */
 int KNC_ENABLE_COUNTER0 ; 
 int KNC_ENABLE_COUNTER1 ; 
 int /*<<< orphan*/  MSR_KNC_IA32_PERF_GLOBAL_CTRL ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void knc_pmu_disable_all(void)
{
	u64 val;

	rdmsrl(MSR_KNC_IA32_PERF_GLOBAL_CTRL, val);
	val &= ~(KNC_ENABLE_COUNTER0|KNC_ENABLE_COUNTER1);
	wrmsrl(MSR_KNC_IA32_PERF_GLOBAL_CTRL, val);
}