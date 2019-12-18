#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* vcore; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {scalar_t__ arch_compat; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 scalar_t__ PVR_ARCH_207 ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kvmppc_power8_compatible(struct kvm_vcpu *vcpu)
{
	if (vcpu->arch.vcore->arch_compat >= PVR_ARCH_207)
		return true;
	if ((!vcpu->arch.vcore->arch_compat) &&
	    cpu_has_feature(CPU_FTR_ARCH_207S))
		return true;
	return false;
}