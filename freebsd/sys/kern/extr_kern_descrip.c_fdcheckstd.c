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
struct thread {int* td_retval; TYPE_1__* td_proc; } ;
struct filedesc {int fd_refcnt; int fd_nfiles; TYPE_2__* fd_ofiles; } ;
typedef  int register_t ;
struct TYPE_4__ {int /*<<< orphan*/ * fde_file; } ;
struct TYPE_3__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  FDDUP_FIXED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int kern_dup (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int kern_openat (struct thread*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
fdcheckstd(struct thread *td)
{
	struct filedesc *fdp;
	register_t save;
	int i, error, devnull;

	fdp = td->td_proc->p_fd;
	KASSERT(fdp->fd_refcnt == 1, ("the fdtable should not be shared"));
	MPASS(fdp->fd_nfiles >= 3);
	devnull = -1;
	for (i = 0; i <= 2; i++) {
		if (fdp->fd_ofiles[i].fde_file != NULL)
			continue;

		save = td->td_retval[0];
		if (devnull != -1) {
			error = kern_dup(td, FDDUP_FIXED, 0, devnull, i);
		} else {
			error = kern_openat(td, AT_FDCWD, "/dev/null",
			    UIO_SYSSPACE, O_RDWR, 0);
			if (error == 0) {
				devnull = td->td_retval[0];
				KASSERT(devnull == i, ("we didn't get our fd"));
			}
		}
		td->td_retval[0] = save;
		if (error != 0)
			return (error);
	}
	return (0);
}