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
struct pdgetpid_args {int /*<<< orphan*/  pidp; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  pid ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_pdgetpid_rights ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int kern_pdgetpid (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
sys_pdgetpid(struct thread *td, struct pdgetpid_args *uap)
{
	pid_t pid;
	int error;

	AUDIT_ARG_FD(uap->fd);
	error = kern_pdgetpid(td, uap->fd, &cap_pdgetpid_rights, &pid);
	if (error == 0)
		error = copyout(&pid, uap->pidp, sizeof(pid));
	return (error);
}