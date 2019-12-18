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
struct kvm_segment {unsigned int selector; int type; unsigned int dpl; int /*<<< orphan*/  present; int /*<<< orphan*/  s; scalar_t__ unusable; } ;

/* Variables and functions */
 unsigned int SEGMENT_RPL_MASK ; 
 int /*<<< orphan*/  VCPU_SREG_SS ; 
 int /*<<< orphan*/  vmx_get_segment (struct kvm_vcpu*,struct kvm_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool stack_segment_valid(struct kvm_vcpu *vcpu)
{
	struct kvm_segment ss;
	unsigned int ss_rpl;

	vmx_get_segment(vcpu, &ss, VCPU_SREG_SS);
	ss_rpl = ss.selector & SEGMENT_RPL_MASK;

	if (ss.unusable)
		return true;
	if (ss.type != 3 && ss.type != 7)
		return false;
	if (!ss.s)
		return false;
	if (ss.dpl != ss_rpl) /* DPL != RPL */
		return false;
	if (!ss.present)
		return false;

	return true;
}