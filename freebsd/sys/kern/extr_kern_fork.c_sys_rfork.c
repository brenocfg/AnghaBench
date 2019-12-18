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
struct thread {int* td_retval; } ;
struct rfork_args {int flags; } ;
struct fork_req {int fr_flags; int* fr_pidp; int /*<<< orphan*/  fr_flags2; } ;
typedef  int /*<<< orphan*/  fr ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FFLAGS (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FR2_DROPSIG_CAUGHT ; 
 int RFFDG ; 
 int RFKERNELONLY ; 
 int RFMEM ; 
 int RFPPWAIT ; 
 int RFPROC ; 
 int RFSPAWN ; 
 int /*<<< orphan*/  bzero (struct fork_req*,int) ; 
 int fork1 (struct thread*,struct fork_req*) ; 

int
sys_rfork(struct thread *td, struct rfork_args *uap)
{
	struct fork_req fr;
	int error, pid;

	/* Don't allow kernel-only flags. */
	if ((uap->flags & RFKERNELONLY) != 0)
		return (EINVAL);
	/* RFSPAWN must not appear with others */
	if ((uap->flags & RFSPAWN) != 0 && uap->flags != RFSPAWN)
		return (EINVAL);

	AUDIT_ARG_FFLAGS(uap->flags);
	bzero(&fr, sizeof(fr));
	if ((uap->flags & RFSPAWN) != 0) {
		fr.fr_flags = RFFDG | RFPROC | RFPPWAIT | RFMEM;
		fr.fr_flags2 = FR2_DROPSIG_CAUGHT;
	} else {
		fr.fr_flags = uap->flags;
	}
	fr.fr_pidp = &pid;
	error = fork1(td, &fr);
	if (error == 0) {
		td->td_retval[0] = pid;
		td->td_retval[1] = 0;
	}
	return (error);
}