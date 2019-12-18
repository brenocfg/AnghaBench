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
struct TYPE_7__ {int /*<<< orphan*/  exit_validity; } ;
struct TYPE_6__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_3__ stat; TYPE_2__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/  pid; } ;
struct TYPE_5__ {int ipb; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVM_EVENT (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  trace_kvm_s390_intercept_validity (struct kvm_vcpu*,int) ; 

__attribute__((used)) static int handle_validity(struct kvm_vcpu *vcpu)
{
	int viwhy = vcpu->arch.sie_block->ipb >> 16;

	vcpu->stat.exit_validity++;
	trace_kvm_s390_intercept_validity(vcpu, viwhy);
	KVM_EVENT(3, "validity intercept 0x%x for pid %u (kvm 0x%pK)", viwhy,
		  current->pid, vcpu->kvm);

	/* do not warn on invalid runtime instrumentation mode */
	WARN_ONCE(viwhy != 0x44, "kvm: unhandled validity intercept 0x%x\n",
		  viwhy);
	return -EINVAL;
}