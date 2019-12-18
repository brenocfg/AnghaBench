#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct thread {TYPE_1__* td_proc; } ;
struct task_struct {unsigned int bsd_ioctl_len; int /*<<< orphan*/ * bsd_ioctl_data; } ;
struct linux_file {int dummy; } ;
struct file_operations {int /*<<< orphan*/  (* unlocked_ioctl ) (struct linux_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* compat_ioctl ) (struct linux_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_2__ {scalar_t__ p_elf_machine; } ;

/* Variables and functions */
 scalar_t__ EM_386 ; 
 int ENOTTY ; 
 int EWOULDBLOCK ; 
 unsigned int IOCPARM_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ LINUX_IOCTL_MIN_PTR ; 
 int LINUX_KQ_FLAG_HAS_READ ; 
 int LINUX_KQ_FLAG_HAS_WRITE ; 
 int OPW (struct file*,struct thread*,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  linux_file_kqfilter_poll (struct linux_file*,int) ; 
 int linux_get_error (struct task_struct*,int) ; 
 int /*<<< orphan*/  stub1 (struct linux_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct linux_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct linux_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_file_ioctl_sub(struct file *fp, struct linux_file *filp,
    const struct file_operations *fop, u_long cmd, caddr_t data,
    struct thread *td)
{
	struct task_struct *task = current;
	unsigned size;
	int error;

	size = IOCPARM_LEN(cmd);
	/* refer to logic in sys_ioctl() */
	if (size > 0) {
		/*
		 * Setup hint for linux_copyin() and linux_copyout().
		 *
		 * Background: Linux code expects a user-space address
		 * while FreeBSD supplies a kernel-space address.
		 */
		task->bsd_ioctl_data = data;
		task->bsd_ioctl_len = size;
		data = (void *)LINUX_IOCTL_MIN_PTR;
	} else {
		/* fetch user-space pointer */
		data = *(void **)data;
	}
#if defined(__amd64__)
	if (td->td_proc->p_elf_machine == EM_386) {
		/* try the compat IOCTL handler first */
		if (fop->compat_ioctl != NULL) {
			error = -OPW(fp, td, fop->compat_ioctl(filp,
			    cmd, (u_long)data));
		} else {
			error = ENOTTY;
		}

		/* fallback to the regular IOCTL handler, if any */
		if (error == ENOTTY && fop->unlocked_ioctl != NULL) {
			error = -OPW(fp, td, fop->unlocked_ioctl(filp,
			    cmd, (u_long)data));
		}
	} else
#endif
	{
		if (fop->unlocked_ioctl != NULL) {
			error = -OPW(fp, td, fop->unlocked_ioctl(filp,
			    cmd, (u_long)data));
		} else {
			error = ENOTTY;
		}
	}
	if (size > 0) {
		task->bsd_ioctl_data = NULL;
		task->bsd_ioctl_len = 0;
	}

	if (error == EWOULDBLOCK) {
		/* update kqfilter status, if any */
		linux_file_kqfilter_poll(filp,
		    LINUX_KQ_FLAG_HAS_READ | LINUX_KQ_FLAG_HAS_WRITE);
	} else {
		error = linux_get_error(task, error);
	}
	return (error);
}