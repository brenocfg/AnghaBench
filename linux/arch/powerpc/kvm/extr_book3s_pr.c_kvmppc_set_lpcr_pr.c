#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  intr_msr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int LPCR_ILE ; 
 int /*<<< orphan*/  MSR_LE ; 

__attribute__((used)) static void kvmppc_set_lpcr_pr(struct kvm_vcpu *vcpu, u64 new_lpcr)
{
	if (new_lpcr & LPCR_ILE)
		vcpu->arch.intr_msr |= MSR_LE;
	else
		vcpu->arch.intr_msr &= ~MSR_LE;
}