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
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 int /*<<< orphan*/  VCPU_SREG_DS ; 
 int /*<<< orphan*/  VCPU_SREG_ES ; 
 int /*<<< orphan*/  VCPU_SREG_FS ; 
 int /*<<< orphan*/  VCPU_SREG_GS ; 
 int /*<<< orphan*/  VCPU_SREG_SS ; 
 int X86_EFLAGS_VM ; 
 int /*<<< orphan*/  code_segment_valid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  cs_ss_rpl_check (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  data_segment_valid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ enable_unrestricted_guest ; 
 int /*<<< orphan*/  is_protmode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  ldtr_valid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  rmode_segment_valid (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_segment_valid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  tr_valid (struct kvm_vcpu*) ; 
 int vmx_get_rflags (struct kvm_vcpu*) ; 

__attribute__((used)) static bool guest_state_valid(struct kvm_vcpu *vcpu)
{
	if (enable_unrestricted_guest)
		return true;

	/* real mode guest state checks */
	if (!is_protmode(vcpu) || (vmx_get_rflags(vcpu) & X86_EFLAGS_VM)) {
		if (!rmode_segment_valid(vcpu, VCPU_SREG_CS))
			return false;
		if (!rmode_segment_valid(vcpu, VCPU_SREG_SS))
			return false;
		if (!rmode_segment_valid(vcpu, VCPU_SREG_DS))
			return false;
		if (!rmode_segment_valid(vcpu, VCPU_SREG_ES))
			return false;
		if (!rmode_segment_valid(vcpu, VCPU_SREG_FS))
			return false;
		if (!rmode_segment_valid(vcpu, VCPU_SREG_GS))
			return false;
	} else {
	/* protected mode guest state checks */
		if (!cs_ss_rpl_check(vcpu))
			return false;
		if (!code_segment_valid(vcpu))
			return false;
		if (!stack_segment_valid(vcpu))
			return false;
		if (!data_segment_valid(vcpu, VCPU_SREG_DS))
			return false;
		if (!data_segment_valid(vcpu, VCPU_SREG_ES))
			return false;
		if (!data_segment_valid(vcpu, VCPU_SREG_FS))
			return false;
		if (!data_segment_valid(vcpu, VCPU_SREG_GS))
			return false;
		if (!tr_valid(vcpu))
			return false;
		if (!ldtr_valid(vcpu))
			return false;
	}
	/* TODO:
	 * - Add checks on RIP
	 * - Add checks on RFLAGS
	 */

	return true;
}