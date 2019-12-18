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
union kvmppc_icp_state {int xisr; int mfrr; scalar_t__ cppr; } ;
typedef  int u32 ;
struct kvmppc_icp {unsigned long server_num; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct kvmppc_icp* icp; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;

/* Variables and functions */
 int H_PARAMETER ; 
 int H_SUCCESS ; 
 union kvmppc_icp_state READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,int) ; 
 struct kvmppc_icp* kvmppc_xics_find_server (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int kvmppc_h_ipoll(struct kvm_vcpu *vcpu, unsigned long server)
{
	union kvmppc_icp_state state;
	struct kvmppc_icp *icp;

	icp = vcpu->arch.icp;
	if (icp->server_num != server) {
		icp = kvmppc_xics_find_server(vcpu->kvm, server);
		if (!icp)
			return H_PARAMETER;
	}
	state = READ_ONCE(icp->state);
	kvmppc_set_gpr(vcpu, 4, ((u32)state.cppr << 24) | state.xisr);
	kvmppc_set_gpr(vcpu, 5, state.mfrr);
	return H_SUCCESS;
}