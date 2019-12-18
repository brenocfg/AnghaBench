#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nip; } ;
struct TYPE_6__ {TYPE_1__ regs; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; int /*<<< orphan*/  address; } ;
struct TYPE_7__ {TYPE_4__ arch; } ;
struct kvm_run {TYPE_3__ debug; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EXITS ; 
#define  EHPRIV_OC_DEBUG 128 
 int EMULATE_DONE ; 
 int EMULATE_EXIT_USER ; 
 int EMULATE_FAIL ; 
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 
 int get_oc (unsigned int) ; 
 int /*<<< orphan*/  kvmppc_account_exit (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmppc_e500_emul_ehpriv(struct kvm_run *run, struct kvm_vcpu *vcpu,
				   unsigned int inst, int *advance)
{
	int emulated = EMULATE_DONE;

	switch (get_oc(inst)) {
	case EHPRIV_OC_DEBUG:
		run->exit_reason = KVM_EXIT_DEBUG;
		run->debug.arch.address = vcpu->arch.regs.nip;
		run->debug.arch.status = 0;
		kvmppc_account_exit(vcpu, DEBUG_EXITS);
		emulated = EMULATE_EXIT_USER;
		*advance = 0;
		break;
	default:
		emulated = EMULATE_FAIL;
	}
	return emulated;
}