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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmcb_ctrl {int /*<<< orphan*/  exitintinfo; } ;
struct svm_softc {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_CTR2 (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCPU_EXITINTINFO ; 
 int /*<<< orphan*/  VMCB_EXITINTINFO_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCB_EXITINTINFO_VECTOR (int /*<<< orphan*/ ) ; 
 struct vmcb_ctrl* svm_get_vmcb_ctrl (struct svm_softc*,int) ; 
 int /*<<< orphan*/  vm_exit_intinfo (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_incr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
svm_save_intinfo(struct svm_softc *svm_sc, int vcpu)
{
	struct vmcb_ctrl *ctrl;
	uint64_t intinfo;

	ctrl  = svm_get_vmcb_ctrl(svm_sc, vcpu);
	intinfo = ctrl->exitintinfo;	
	if (!VMCB_EXITINTINFO_VALID(intinfo))
		return;

	/*
	 * From APMv2, Section "Intercepts during IDT interrupt delivery"
	 *
	 * If a #VMEXIT happened during event delivery then record the event
	 * that was being delivered.
	 */
	VCPU_CTR2(svm_sc->vm, vcpu, "SVM:Pending INTINFO(0x%lx), vector=%d.\n",
		intinfo, VMCB_EXITINTINFO_VECTOR(intinfo));
	vmm_stat_incr(svm_sc->vm, vcpu, VCPU_EXITINTINFO, 1);
	vm_exit_intinfo(svm_sc->vm, vcpu, intinfo);
}