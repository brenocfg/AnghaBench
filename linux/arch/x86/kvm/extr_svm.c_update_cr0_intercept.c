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
typedef  int ulong ;
typedef  int u64 ;
struct TYPE_5__ {int cr0; } ;
struct TYPE_6__ {TYPE_1__ arch; } ;
struct vcpu_svm {TYPE_4__* vmcb; TYPE_2__ vcpu; } ;
struct TYPE_7__ {int cr0; } ;
struct TYPE_8__ {TYPE_3__ save; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERCEPT_CR0_READ ; 
 int /*<<< orphan*/  INTERCEPT_CR0_WRITE ; 
 int SVM_CR0_SELECTIVE_MASK ; 
 int /*<<< orphan*/  VMCB_CR ; 
 int /*<<< orphan*/  clr_cr_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_dirty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cr_intercept (struct vcpu_svm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_cr0_intercept(struct vcpu_svm *svm)
{
	ulong gcr0 = svm->vcpu.arch.cr0;
	u64 *hcr0 = &svm->vmcb->save.cr0;

	*hcr0 = (*hcr0 & ~SVM_CR0_SELECTIVE_MASK)
		| (gcr0 & SVM_CR0_SELECTIVE_MASK);

	mark_dirty(svm->vmcb, VMCB_CR);

	if (gcr0 == *hcr0) {
		clr_cr_intercept(svm, INTERCEPT_CR0_READ);
		clr_cr_intercept(svm, INTERCEPT_CR0_WRITE);
	} else {
		set_cr_intercept(svm, INTERCEPT_CR0_READ);
		set_cr_intercept(svm, INTERCEPT_CR0_WRITE);
	}
}