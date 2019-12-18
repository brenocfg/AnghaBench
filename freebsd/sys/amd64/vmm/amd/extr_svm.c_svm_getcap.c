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
 int ENOENT ; 
 int /*<<< orphan*/  VMCB_CTRL1_INTCPT ; 
 int /*<<< orphan*/  VMCB_INTCPT_HLT ; 
 int /*<<< orphan*/  VMCB_INTCPT_PAUSE ; 
#define  VM_CAP_HALT_EXIT 130 
#define  VM_CAP_PAUSE_EXIT 129 
#define  VM_CAP_UNRESTRICTED_GUEST 128 
 int svm_get_intercept (struct svm_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
svm_getcap(void *arg, int vcpu, int type, int *retval)
{
	struct svm_softc *sc;
	int error;

	sc = arg;
	error = 0;

	switch (type) {
	case VM_CAP_HALT_EXIT:
		*retval = svm_get_intercept(sc, vcpu, VMCB_CTRL1_INTCPT,
		    VMCB_INTCPT_HLT);
		break;
	case VM_CAP_PAUSE_EXIT:
		*retval = svm_get_intercept(sc, vcpu, VMCB_CTRL1_INTCPT,
		    VMCB_INTCPT_PAUSE);
		break;
	case VM_CAP_UNRESTRICTED_GUEST:
		*retval = 1;	/* unrestricted guest is always enabled */
		break;
	default:
		error = ENOENT;
		break;
	}
	return (error);
}