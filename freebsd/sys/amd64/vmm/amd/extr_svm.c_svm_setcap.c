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
struct svm_softc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  VMCB_CTRL1_INTCPT ; 
 int /*<<< orphan*/  VMCB_INTCPT_HLT ; 
 int /*<<< orphan*/  VMCB_INTCPT_PAUSE ; 
#define  VM_CAP_HALT_EXIT 130 
#define  VM_CAP_PAUSE_EXIT 129 
#define  VM_CAP_UNRESTRICTED_GUEST 128 
 int /*<<< orphan*/  svm_set_intercept (struct svm_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
svm_setcap(void *arg, int vcpu, int type, int val)
{
	struct svm_softc *sc;
	int error;

	sc = arg;
	error = 0;
	switch (type) {
	case VM_CAP_HALT_EXIT:
		svm_set_intercept(sc, vcpu, VMCB_CTRL1_INTCPT,
		    VMCB_INTCPT_HLT, val);
		break;
	case VM_CAP_PAUSE_EXIT:
		svm_set_intercept(sc, vcpu, VMCB_CTRL1_INTCPT,
		    VMCB_INTCPT_PAUSE, val);
		break;
	case VM_CAP_UNRESTRICTED_GUEST:
		/* Unrestricted guest execution cannot be disabled in SVM */
		if (val == 0)
			error = EINVAL;
		break;
	default:
		error = ENOENT;
		break;
	}
	return (error);
}