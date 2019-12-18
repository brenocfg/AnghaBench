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
typedef  union kvmppc_one_reg {int dummy; } kvmppc_one_reg ;
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int kvmppc_get_one_reg_e500_tlb (struct kvm_vcpu*,int /*<<< orphan*/ ,union kvmppc_one_reg*) ; 

__attribute__((used)) static int kvmppc_get_one_reg_e500(struct kvm_vcpu *vcpu, u64 id,
				   union kvmppc_one_reg *val)
{
	int r = kvmppc_get_one_reg_e500_tlb(vcpu, id, val);
	return r;
}