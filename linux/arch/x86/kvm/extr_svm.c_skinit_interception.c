#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vcpu_svm {int /*<<< orphan*/  vcpu; TYPE_2__* vmcb; } ;
struct TYPE_3__ {int /*<<< orphan*/  rip; } ;
struct TYPE_4__ {TYPE_1__ save; } ;

/* Variables and functions */
 int /*<<< orphan*/  UD_VECTOR ; 
 int /*<<< orphan*/  kvm_queue_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_rax_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_kvm_skinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skinit_interception(struct vcpu_svm *svm)
{
	trace_kvm_skinit(svm->vmcb->save.rip, kvm_rax_read(&svm->vcpu));

	kvm_queue_exception(&svm->vcpu, UD_VECTOR);
	return 1;
}