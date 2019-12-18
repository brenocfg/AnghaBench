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
 int /*<<< orphan*/  CAPFAIL_SYSCALL ; 
 int ECAPMODE ; 
 int EINVAL ; 
 int /*<<< orphan*/  Giant ; 
 scalar_t__ IN_CAPABILITY_MODE (struct thread*) ; 
 int /*<<< orphan*/  KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_CAPFAIL ; 
#define  SPARC_SIGTRAMP_INSTALL 129 
#define  SPARC_UTRAP_INSTALL 128 
 int /*<<< orphan*/  ktrcapfail (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int sparc_sigtramp_install (struct thread*,int /*<<< orphan*/ ) ; 
 int sparc_utrap_install (struct thread*,int /*<<< orphan*/ ) ; 

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
		case SPARC_SIGTRAMP_INSTALL:
		case SPARC_UTRAP_INSTALL:
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

	mtx_lock(&Giant);
	switch (uap->op) {
	case SPARC_SIGTRAMP_INSTALL:
		error = sparc_sigtramp_install(td, uap->parms);
		break;
	case SPARC_UTRAP_INSTALL:
		error = sparc_utrap_install(td, uap->parms);
		break;
	default:
		error = EINVAL;
		break;
	}
	mtx_unlock(&Giant);
	return (error);
}