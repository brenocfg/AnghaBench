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
 int /*<<< orphan*/  inject_abt64 (struct kvm_vcpu*,int,unsigned long) ; 
 int /*<<< orphan*/  kvm_inject_pabt32 (struct kvm_vcpu*,unsigned long) ; 
 scalar_t__ vcpu_el1_is_32bit (struct kvm_vcpu*) ; 

void kvm_inject_pabt(struct kvm_vcpu *vcpu, unsigned long addr)
{
	if (vcpu_el1_is_32bit(vcpu))
		kvm_inject_pabt32(vcpu, addr);
	else
		inject_abt64(vcpu, true, addr);
}