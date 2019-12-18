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
struct procdesc {struct proc* pd_proc; } ;
struct proc {int dummy; } ;
struct file {scalar_t__ f_type; struct procdesc* f_data; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 scalar_t__ DTYPE_PROCDESC ; 
 int EBADF ; 
 int ESRCH ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

int
procdesc_find(struct thread *td, int fd, cap_rights_t *rightsp,
    struct proc **p)
{
	struct procdesc *pd;
	struct file *fp;
	int error;

	error = fget(td, fd, rightsp, &fp);
	if (error)
		return (error);
	if (fp->f_type != DTYPE_PROCDESC) {
		error = EBADF;
		goto out;
	}
	pd = fp->f_data;
	sx_slock(&proctree_lock);
	if (pd->pd_proc != NULL) {
		*p = pd->pd_proc;
		PROC_LOCK(*p);
	} else
		error = ESRCH;
	sx_sunlock(&proctree_lock);
out:
	fdrop(fp, td);
	return (error);
}