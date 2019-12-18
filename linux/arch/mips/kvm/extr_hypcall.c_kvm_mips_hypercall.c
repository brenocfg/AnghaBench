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
 unsigned long KVM_ENOSYS ; 
 int RESUME_GUEST ; 

__attribute__((used)) static int kvm_mips_hypercall(struct kvm_vcpu *vcpu, unsigned long num,
			      const unsigned long *args, unsigned long *hret)
{
	/* Report unimplemented hypercall to guest */
	*hret = -KVM_ENOSYS;
	return RESUME_GUEST;
}