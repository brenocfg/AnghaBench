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
struct TYPE_3__ {int /*<<< orphan*/  msr; } ;
struct TYPE_4__ {int ceded; scalar_t__ prodded; TYPE_1__ shregs; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_EE ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void kvmppc_nested_cede(struct kvm_vcpu *vcpu)
{
	vcpu->arch.shregs.msr |= MSR_EE;
	vcpu->arch.ceded = 1;
	smp_mb();
	if (vcpu->arch.prodded) {
		vcpu->arch.prodded = 0;
		smp_mb();
		vcpu->arch.ceded = 0;
	}
}