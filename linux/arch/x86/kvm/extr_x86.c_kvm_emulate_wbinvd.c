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
 int /*<<< orphan*/  kvm_emulate_wbinvd_noskip (struct kvm_vcpu*) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 

int kvm_emulate_wbinvd(struct kvm_vcpu *vcpu)
{
	kvm_emulate_wbinvd_noskip(vcpu);
	return kvm_skip_emulated_instruction(vcpu);
}