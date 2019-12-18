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
struct kvm_segment {int selector; int dpl; int s; } ;

/* Variables and functions */
 int SEGMENT_RPL_MASK ; 
 int VCPU_SREG_CS ; 
 int VCPU_SREG_SS ; 
 int /*<<< orphan*/  emulate_invalid_guest_state ; 
 int /*<<< orphan*/  vmx_set_segment (struct kvm_vcpu*,struct kvm_segment*,int) ; 

__attribute__((used)) static void fix_pmode_seg(struct kvm_vcpu *vcpu, int seg,
		struct kvm_segment *save)
{
	if (!emulate_invalid_guest_state) {
		/*
		 * CS and SS RPL should be equal during guest entry according
		 * to VMX spec, but in reality it is not always so. Since vcpu
		 * is in the middle of the transition from real mode to
		 * protected mode it is safe to assume that RPL 0 is a good
		 * default value.
		 */
		if (seg == VCPU_SREG_CS || seg == VCPU_SREG_SS)
			save->selector &= ~SEGMENT_RPL_MASK;
		save->dpl = save->selector & SEGMENT_RPL_MASK;
		save->s = 1;
	}
	vmx_set_segment(vcpu, save, seg);
}