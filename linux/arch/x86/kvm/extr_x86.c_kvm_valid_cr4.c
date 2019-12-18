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
 unsigned long CR4_RESERVED_BITS ; 
 int EINVAL ; 
 unsigned long X86_CR4_FSGSBASE ; 
 unsigned long X86_CR4_LA57 ; 
 unsigned long X86_CR4_OSXSAVE ; 
 unsigned long X86_CR4_PKE ; 
 unsigned long X86_CR4_SMAP ; 
 unsigned long X86_CR4_SMEP ; 
 unsigned long X86_CR4_UMIP ; 
 int /*<<< orphan*/  X86_FEATURE_FSGSBASE ; 
 int /*<<< orphan*/  X86_FEATURE_LA57 ; 
 int /*<<< orphan*/  X86_FEATURE_PKU ; 
 int /*<<< orphan*/  X86_FEATURE_SMAP ; 
 int /*<<< orphan*/  X86_FEATURE_SMEP ; 
 int /*<<< orphan*/  X86_FEATURE_UMIP ; 
 int /*<<< orphan*/  X86_FEATURE_XSAVE ; 
 int /*<<< orphan*/  guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_valid_cr4(struct kvm_vcpu *vcpu, unsigned long cr4)
{
	if (cr4 & CR4_RESERVED_BITS)
		return -EINVAL;

	if (!guest_cpuid_has(vcpu, X86_FEATURE_XSAVE) && (cr4 & X86_CR4_OSXSAVE))
		return -EINVAL;

	if (!guest_cpuid_has(vcpu, X86_FEATURE_SMEP) && (cr4 & X86_CR4_SMEP))
		return -EINVAL;

	if (!guest_cpuid_has(vcpu, X86_FEATURE_SMAP) && (cr4 & X86_CR4_SMAP))
		return -EINVAL;

	if (!guest_cpuid_has(vcpu, X86_FEATURE_FSGSBASE) && (cr4 & X86_CR4_FSGSBASE))
		return -EINVAL;

	if (!guest_cpuid_has(vcpu, X86_FEATURE_PKU) && (cr4 & X86_CR4_PKE))
		return -EINVAL;

	if (!guest_cpuid_has(vcpu, X86_FEATURE_LA57) && (cr4 & X86_CR4_LA57))
		return -EINVAL;

	if (!guest_cpuid_has(vcpu, X86_FEATURE_UMIP) && (cr4 & X86_CR4_UMIP))
		return -EINVAL;

	return 0;
}