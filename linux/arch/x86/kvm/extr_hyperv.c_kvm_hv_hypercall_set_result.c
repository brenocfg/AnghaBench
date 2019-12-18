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
 int is_64_bit_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rax_write (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_rdx_write (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void kvm_hv_hypercall_set_result(struct kvm_vcpu *vcpu, u64 result)
{
	bool longmode;

	longmode = is_64_bit_mode(vcpu);
	if (longmode)
		kvm_rax_write(vcpu, result);
	else {
		kvm_rdx_write(vcpu, result >> 32);
		kvm_rax_write(vcpu, result & 0xffffffff);
	}
}