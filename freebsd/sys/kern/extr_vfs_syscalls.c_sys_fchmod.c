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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct file {int dummy; } ;
struct fchmod_args {int /*<<< orphan*/  mode; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_ARG_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_fchmod_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**) ; 
 int fo_chmod (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 

int
sys_fchmod(struct thread *td, struct fchmod_args *uap)
{
	struct file *fp;
	int error;

	AUDIT_ARG_FD(uap->fd);
	AUDIT_ARG_MODE(uap->mode);

	error = fget(td, uap->fd, &cap_fchmod_rights, &fp);
	if (error != 0)
		return (error);
	error = fo_chmod(fp, uap->mode, td->td_ucred, td);
	fdrop(fp, td);
	return (error);
}