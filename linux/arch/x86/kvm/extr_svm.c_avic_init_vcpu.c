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
struct vcpu_svm {int /*<<< orphan*/  dfr_reg; int /*<<< orphan*/  ir_list_lock; int /*<<< orphan*/  ir_list; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DFR_FLAT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int avic_init_backing_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_vcpu_apicv_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int avic_init_vcpu(struct vcpu_svm *svm)
{
	int ret;

	if (!kvm_vcpu_apicv_active(&svm->vcpu))
		return 0;

	ret = avic_init_backing_page(&svm->vcpu);
	if (ret)
		return ret;

	INIT_LIST_HEAD(&svm->ir_list);
	spin_lock_init(&svm->ir_list_lock);
	svm->dfr_reg = APIC_DFR_FLAT;

	return ret;
}