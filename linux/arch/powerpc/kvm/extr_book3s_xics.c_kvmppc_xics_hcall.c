#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct kvmppc_xics {scalar_t__ real_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  icp; } ;
struct kvm_vcpu {TYPE_3__* kvm; TYPE_1__ arch; } ;
struct TYPE_5__ {struct kvmppc_xics* xics; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
#define  H_CPPR 133 
#define  H_EOI 132 
 int H_HARDWARE ; 
#define  H_IPI 131 
#define  H_IPOLL 130 
 int H_SUCCESS ; 
#define  H_XIRR 129 
#define  H_XIRR_X 128 
 unsigned long get_tb () ; 
 scalar_t__ is_kvmppc_hv_enabled (TYPE_3__*) ; 
 int /*<<< orphan*/  kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_h_cppr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvmppc_h_eoi (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvmppc_h_ipi (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvmppc_h_ipoll (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 unsigned long kvmppc_h_xirr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,unsigned long) ; 
 int kvmppc_xics_rm_complete (struct kvm_vcpu*,int) ; 

int kvmppc_xics_hcall(struct kvm_vcpu *vcpu, u32 req)
{
	struct kvmppc_xics *xics = vcpu->kvm->arch.xics;
	unsigned long res;
	int rc = H_SUCCESS;

	/* Check if we have an ICP */
	if (!xics || !vcpu->arch.icp)
		return H_HARDWARE;

	/* These requests don't have real-mode implementations at present */
	switch (req) {
	case H_XIRR_X:
		res = kvmppc_h_xirr(vcpu);
		kvmppc_set_gpr(vcpu, 4, res);
		kvmppc_set_gpr(vcpu, 5, get_tb());
		return rc;
	case H_IPOLL:
		rc = kvmppc_h_ipoll(vcpu, kvmppc_get_gpr(vcpu, 4));
		return rc;
	}

	/* Check for real mode returning too hard */
	if (xics->real_mode && is_kvmppc_hv_enabled(vcpu->kvm))
		return kvmppc_xics_rm_complete(vcpu, req);

	switch (req) {
	case H_XIRR:
		res = kvmppc_h_xirr(vcpu);
		kvmppc_set_gpr(vcpu, 4, res);
		break;
	case H_CPPR:
		kvmppc_h_cppr(vcpu, kvmppc_get_gpr(vcpu, 4));
		break;
	case H_EOI:
		rc = kvmppc_h_eoi(vcpu, kvmppc_get_gpr(vcpu, 4));
		break;
	case H_IPI:
		rc = kvmppc_h_ipi(vcpu, kvmppc_get_gpr(vcpu, 4),
				  kvmppc_get_gpr(vcpu, 5));
		break;
	}

	return rc;
}