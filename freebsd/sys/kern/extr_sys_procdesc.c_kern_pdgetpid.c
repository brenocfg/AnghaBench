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
struct file {scalar_t__ f_type; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 scalar_t__ DTYPE_PROCDESC ; 
 int EBADF ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int /*<<< orphan*/  procdesc_pid (struct file*) ; 

int
kern_pdgetpid(struct thread *td, int fd, cap_rights_t *rightsp, pid_t *pidp)
{
	struct file *fp;
	int error;

	error = fget(td, fd, rightsp, &fp);
	if (error)
		return (error);
	if (fp->f_type != DTYPE_PROCDESC) {
		error = EBADF;
		goto out;
	}
	*pidp = procdesc_pid(fp);
out:
	fdrop(fp, td);
	return (error);
}