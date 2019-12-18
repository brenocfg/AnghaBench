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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int kvm_pmu_rdpmc (struct kvm_vcpu*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kvm_rax_write (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_rcx_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rdx_write (struct kvm_vcpu*,int) ; 

bool kvm_rdpmc(struct kvm_vcpu *vcpu)
{
	u32 ecx = kvm_rcx_read(vcpu);
	u64 data;
	int err;

	err = kvm_pmu_rdpmc(vcpu, ecx, &data);
	if (err)
		return err;
	kvm_rax_write(vcpu, (u32)data);
	kvm_rdx_write(vcpu, data >> 32);
	return err;
}