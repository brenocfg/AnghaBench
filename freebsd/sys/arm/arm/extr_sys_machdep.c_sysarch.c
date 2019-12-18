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
struct thread {int dummy; } ;
struct sysarch_args {int op; int /*<<< orphan*/  parms; } ;

/* Variables and functions */
#define  ARM_DRAIN_WRITEBUF 132 
#define  ARM_GET_TP 131 
#define  ARM_GET_VFPSTATE 130 
#define  ARM_SET_TP 129 
#define  ARM_SYNC_ICACHE 128 
 int /*<<< orphan*/  CAPFAIL_SYSCALL ; 
 int ECAPMODE ; 
 int EINVAL ; 
 scalar_t__ IN_CAPABILITY_MODE (struct thread*) ; 
 int /*<<< orphan*/  KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_CAPFAIL ; 
 int arm32_drain_writebuf (struct thread*,int /*<<< orphan*/ ) ; 
 int arm32_get_tp (struct thread*,int /*<<< orphan*/ ) ; 
 int arm32_set_tp (struct thread*,int /*<<< orphan*/ ) ; 
 int arm32_sync_icache (struct thread*,int /*<<< orphan*/ ) ; 
 int arm_get_vfpstate (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrcapfail (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
sysarch(struct thread *td, struct sysarch_args *uap)
{
	int error;

#ifdef CAPABILITY_MODE
	/*
	 * When adding new operations, add a new case statement here to
	 * explicitly indicate whether or not the operation is safe to
	 * perform in capability mode.
	 */
	if (IN_CAPABILITY_MODE(td)) {
		switch (uap->op) {
		case ARM_SYNC_ICACHE:
		case ARM_DRAIN_WRITEBUF:
		case ARM_SET_TP:
		case ARM_GET_TP:
		case ARM_GET_VFPSTATE:
			break;

		default:
#ifdef KTRACE
			if (KTRPOINT(td, KTR_CAPFAIL))
				ktrcapfail(CAPFAIL_SYSCALL, NULL, NULL);
#endif
			return (ECAPMODE);
		}
	}
#endif

	switch (uap->op) {
	case ARM_SYNC_ICACHE:
		error = arm32_sync_icache(td, uap->parms);
		break;
	case ARM_DRAIN_WRITEBUF:
		error = arm32_drain_writebuf(td, uap->parms);
		break;
	case ARM_SET_TP:
		error = arm32_set_tp(td, uap->parms);
		break;
	case ARM_GET_TP:
		error = arm32_get_tp(td, uap->parms);
		break;
	case ARM_GET_VFPSTATE:
		error = arm_get_vfpstate(td, uap->parms);
		break;
	default:
		error = EINVAL;
		break;
	}
	return (error);
}