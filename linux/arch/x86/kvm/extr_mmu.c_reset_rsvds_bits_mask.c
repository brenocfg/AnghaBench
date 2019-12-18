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
struct kvm_mmu {int /*<<< orphan*/  nx; int /*<<< orphan*/  root_level; int /*<<< orphan*/  guest_rsvd_check; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_GBPAGES ; 
 int /*<<< orphan*/  __reset_rsvds_bits_mask (struct kvm_vcpu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid_maxphyaddr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guest_cpuid_is_amd (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_pse (struct kvm_vcpu*) ; 

__attribute__((used)) static void reset_rsvds_bits_mask(struct kvm_vcpu *vcpu,
				  struct kvm_mmu *context)
{
	__reset_rsvds_bits_mask(vcpu, &context->guest_rsvd_check,
				cpuid_maxphyaddr(vcpu), context->root_level,
				context->nx,
				guest_cpuid_has(vcpu, X86_FEATURE_GBPAGES),
				is_pse(vcpu), guest_cpuid_is_amd(vcpu));
}