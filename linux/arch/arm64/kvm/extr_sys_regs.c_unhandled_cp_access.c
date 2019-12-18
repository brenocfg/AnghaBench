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
typedef  int u8 ;
struct sys_reg_params {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
#define  ESR_ELx_EC_CP14_64 131 
#define  ESR_ELx_EC_CP14_MR 130 
#define  ESR_ELx_EC_CP15_32 129 
#define  ESR_ELx_EC_CP15_64 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kvm_err (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_undefined (struct kvm_vcpu*) ; 
 int kvm_vcpu_trap_get_class (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  print_sys_reg_instr (struct sys_reg_params*) ; 
 int /*<<< orphan*/ * vcpu_cpsr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/ * vcpu_pc (struct kvm_vcpu*) ; 

__attribute__((used)) static void unhandled_cp_access(struct kvm_vcpu *vcpu,
				struct sys_reg_params *params)
{
	u8 hsr_ec = kvm_vcpu_trap_get_class(vcpu);
	int cp = -1;

	switch(hsr_ec) {
	case ESR_ELx_EC_CP15_32:
	case ESR_ELx_EC_CP15_64:
		cp = 15;
		break;
	case ESR_ELx_EC_CP14_MR:
	case ESR_ELx_EC_CP14_64:
		cp = 14;
		break;
	default:
		WARN_ON(1);
	}

	kvm_err("Unsupported guest CP%d access at: %08lx [%08lx]\n",
		cp, *vcpu_pc(vcpu), *vcpu_cpsr(vcpu));
	print_sys_reg_instr(params);
	kvm_inject_undefined(vcpu);
}