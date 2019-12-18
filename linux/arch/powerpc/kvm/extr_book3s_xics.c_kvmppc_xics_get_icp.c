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
union kvmppc_icp_state {scalar_t__ pending_pri; scalar_t__ mfrr; scalar_t__ xisr; scalar_t__ cppr; } ;
typedef  int u64 ;
struct kvmppc_icp {union kvmppc_icp_state state; } ;
struct TYPE_2__ {struct kvmppc_icp* icp; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int KVM_REG_PPC_ICP_CPPR_SHIFT ; 
 int KVM_REG_PPC_ICP_MFRR_SHIFT ; 
 int KVM_REG_PPC_ICP_PPRI_SHIFT ; 
 int KVM_REG_PPC_ICP_XISR_SHIFT ; 

u64 kvmppc_xics_get_icp(struct kvm_vcpu *vcpu)
{
	struct kvmppc_icp *icp = vcpu->arch.icp;
	union kvmppc_icp_state state;

	if (!icp)
		return 0;
	state = icp->state;
	return ((u64)state.cppr << KVM_REG_PPC_ICP_CPPR_SHIFT) |
		((u64)state.xisr << KVM_REG_PPC_ICP_XISR_SHIFT) |
		((u64)state.mfrr << KVM_REG_PPC_ICP_MFRR_SHIFT) |
		((u64)state.pending_pri << KVM_REG_PPC_ICP_PPRI_SHIFT);
}