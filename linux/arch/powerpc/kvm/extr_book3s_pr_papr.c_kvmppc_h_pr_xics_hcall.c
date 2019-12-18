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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,long) ; 
 long kvmppc_xics_hcall (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmppc_h_pr_xics_hcall(struct kvm_vcpu *vcpu, u32 cmd)
{
	long rc = kvmppc_xics_hcall(vcpu, cmd);
	kvmppc_set_gpr(vcpu, 3, rc);
	return EMULATE_DONE;
}