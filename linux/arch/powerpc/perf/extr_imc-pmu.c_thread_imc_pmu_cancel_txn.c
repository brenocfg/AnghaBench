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
struct pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_pmu_enable (struct pmu*) ; 

__attribute__((used)) static void thread_imc_pmu_cancel_txn(struct pmu *pmu)
{
	perf_pmu_enable(pmu);
}