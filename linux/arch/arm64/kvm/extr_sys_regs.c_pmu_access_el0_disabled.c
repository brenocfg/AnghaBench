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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARMV8_PMU_USERENR_EN ; 
 int check_pmu_access_disabled (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pmu_access_el0_disabled(struct kvm_vcpu *vcpu)
{
	return check_pmu_access_disabled(vcpu, ARMV8_PMU_USERENR_EN);
}