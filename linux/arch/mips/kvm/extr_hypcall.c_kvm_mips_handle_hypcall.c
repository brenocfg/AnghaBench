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
struct TYPE_2__ {unsigned long* gprs; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int MAX_HYPCALL_ARGS ; 
 int kvm_mips_hypercall (struct kvm_vcpu*,unsigned long,unsigned long*,unsigned long*) ; 

int kvm_mips_handle_hypcall(struct kvm_vcpu *vcpu)
{
	unsigned long num, args[MAX_HYPCALL_ARGS];

	/* read hypcall number and arguments */
	num = vcpu->arch.gprs[2];	/* v0 */
	args[0] = vcpu->arch.gprs[4];	/* a0 */
	args[1] = vcpu->arch.gprs[5];	/* a1 */
	args[2] = vcpu->arch.gprs[6];	/* a2 */
	args[3] = vcpu->arch.gprs[7];	/* a3 */

	return kvm_mips_hypercall(vcpu, num,
				  args, &vcpu->arch.gprs[2] /* v0 */);
}