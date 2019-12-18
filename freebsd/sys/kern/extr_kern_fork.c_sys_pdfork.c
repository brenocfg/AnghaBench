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
struct pdfork_args {int /*<<< orphan*/  fdp; int /*<<< orphan*/  flags; } ;
struct fork_req {int fr_flags; int* fr_pidp; int* fr_pd_fd; int /*<<< orphan*/  fr_pd_flags; } ;
typedef  int /*<<< orphan*/  fr ;
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 int RFFDG ; 
 int RFPROC ; 
 int RFPROCDESC ; 
 int /*<<< orphan*/  bzero (struct fork_req*,int) ; 
 int copyout (int*,int /*<<< orphan*/ ,int) ; 
 int fork1 (struct thread*,struct fork_req*) ; 

int
sys_pdfork(struct thread *td, struct pdfork_args *uap)
{
	struct fork_req fr;
	int error, fd, pid;

	bzero(&fr, sizeof(fr));
	fr.fr_flags = RFFDG | RFPROC | RFPROCDESC;
	fr.fr_pidp = &pid;
	fr.fr_pd_fd = &fd;
	fr.fr_pd_flags = uap->flags;
	/*
	 * It is necessary to return fd by reference because 0 is a valid file
	 * descriptor number, and the child needs to be able to distinguish
	 * itself from the parent using the return value.
	 */
	error = fork1(td, &fr);
	if (error == 0) {
		td->td_retval[0] = pid;
		td->td_retval[1] = 0;
		error = copyout(&fd, uap->fdp, sizeof(fd));
	}
	return (error);
}