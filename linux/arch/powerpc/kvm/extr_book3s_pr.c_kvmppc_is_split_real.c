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
typedef  int ulong ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int MSR_DR ; 
 int MSR_IR ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 

__attribute__((used)) static bool kvmppc_is_split_real(struct kvm_vcpu *vcpu)
{
	ulong msr = kvmppc_get_msr(vcpu);
	return (msr & (MSR_IR|MSR_DR)) == MSR_DR;
}