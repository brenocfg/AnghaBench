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
struct thread {int /*<<< orphan*/  td_ucred; int /*<<< orphan*/  td_proc; } ;
struct file {int f_flag; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_FILE (int /*<<< orphan*/ ,struct file*) ; 
 int EINVAL ; 
 int FWRITE ; 
 int /*<<< orphan*/  cap_ftruncate_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int fo_truncate (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 

int
kern_ftruncate(struct thread *td, int fd, off_t length)
{
	struct file *fp;
	int error;

	AUDIT_ARG_FD(fd);
	if (length < 0)
		return (EINVAL);
	error = fget(td, fd, &cap_ftruncate_rights, &fp);
	if (error)
		return (error);
	AUDIT_ARG_FILE(td->td_proc, fp);
	if (!(fp->f_flag & FWRITE)) {
		fdrop(fp, td);
		return (EINVAL);
	}
	error = fo_truncate(fp, length, td->td_ucred, td);
	fdrop(fp, td);
	return (error);
}