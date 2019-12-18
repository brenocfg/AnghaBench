#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hflags; } ;
struct TYPE_5__ {int /*<<< orphan*/  nmi_window_exits; } ;
struct TYPE_7__ {TYPE_2__ arch; TYPE_1__ stat; } ;
struct vcpu_svm {TYPE_3__ vcpu; int /*<<< orphan*/  nmi_iret_rip; } ;

/* Variables and functions */
 int /*<<< orphan*/  HF_IRET_MASK ; 
 int /*<<< orphan*/  INTERCEPT_IRET ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  clr_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  kvm_rip_read (TYPE_3__*) ; 

__attribute__((used)) static int iret_interception(struct vcpu_svm *svm)
{
	++svm->vcpu.stat.nmi_window_exits;
	clr_intercept(svm, INTERCEPT_IRET);
	svm->vcpu.arch.hflags |= HF_IRET_MASK;
	svm->nmi_iret_rip = kvm_rip_read(&svm->vcpu);
	kvm_make_request(KVM_REQ_EVENT, &svm->vcpu);
	return 1;
}