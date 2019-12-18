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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int EFER_FFXSR ; 
 int EFER_LMA ; 
 int EFER_LME ; 
 int EFER_NX ; 
 int EFER_SVME ; 
 int /*<<< orphan*/  X86_FEATURE_FXSR_OPT ; 
 int /*<<< orphan*/  X86_FEATURE_LM ; 
 int /*<<< orphan*/  X86_FEATURE_NX ; 
 int /*<<< orphan*/  X86_FEATURE_SVM ; 
 int /*<<< orphan*/  guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __kvm_valid_efer(struct kvm_vcpu *vcpu, u64 efer)
{
	if (efer & EFER_FFXSR && !guest_cpuid_has(vcpu, X86_FEATURE_FXSR_OPT))
		return false;

	if (efer & EFER_SVME && !guest_cpuid_has(vcpu, X86_FEATURE_SVM))
		return false;

	if (efer & (EFER_LME | EFER_LMA) &&
	    !guest_cpuid_has(vcpu, X86_FEATURE_LM))
		return false;

	if (efer & EFER_NX && !guest_cpuid_has(vcpu, X86_FEATURE_NX))
		return false;

	return true;

}