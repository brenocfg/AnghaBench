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
struct kvm_pmu {int /*<<< orphan*/  global_ctrl; } ;
struct kvm_pmc {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 struct kvm_pmu* pmc_to_pmu (struct kvm_pmc*) ; 
 int test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static bool intel_pmc_is_enabled(struct kvm_pmc *pmc)
{
	struct kvm_pmu *pmu = pmc_to_pmu(pmc);

	return test_bit(pmc->idx, (unsigned long *)&pmu->global_ctrl);
}