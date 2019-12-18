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
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 long H_TOO_HARD ; 
 long kvmppc_h_logical_ci_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,long) ; 

__attribute__((used)) static int kvmppc_h_pr_logical_ci_load(struct kvm_vcpu *vcpu)
{
	long rc;

	rc = kvmppc_h_logical_ci_load(vcpu);
	if (rc == H_TOO_HARD)
		return EMULATE_FAIL;
	kvmppc_set_gpr(vcpu, 3, rc);
	return EMULATE_DONE;
}