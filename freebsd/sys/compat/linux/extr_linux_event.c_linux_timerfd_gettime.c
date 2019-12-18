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
struct timerfd {int /*<<< orphan*/  tfd_lock; } ;
struct thread {int dummy; } ;
struct linux_timerfd_gettime_args {int /*<<< orphan*/  old_value; int /*<<< orphan*/  fd; } ;
struct l_itimerspec {int dummy; } ;
struct itimerspec {int dummy; } ;
struct file {scalar_t__ f_type; struct timerfd* f_data; } ;
typedef  int /*<<< orphan*/  lots ;

/* Variables and functions */
 scalar_t__ DTYPE_LINUXTFD ; 
 int EINVAL ; 
 int /*<<< orphan*/  cap_read_rights ; 
 int copyout (struct l_itimerspec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**) ; 
 int /*<<< orphan*/  linux_timerfd_curval (struct timerfd*,struct itimerspec*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int native_to_linux_itimerspec (struct l_itimerspec*,struct itimerspec*) ; 

int
linux_timerfd_gettime(struct thread *td, struct linux_timerfd_gettime_args *args)
{
	struct l_itimerspec lots;
	struct itimerspec ots;
	struct timerfd *tfd;
	struct file *fp;
	int error;

	error = fget(td, args->fd, &cap_read_rights, &fp);
	if (error != 0)
		return (error);
	tfd = fp->f_data;
	if (fp->f_type != DTYPE_LINUXTFD || tfd == NULL) {
		error = EINVAL;
		goto out;
	}

	mtx_lock(&tfd->tfd_lock);
	linux_timerfd_curval(tfd, &ots);
	mtx_unlock(&tfd->tfd_lock);

	error = native_to_linux_itimerspec(&lots, &ots);
	if (error == 0)
		error = copyout(&lots, args->old_value, sizeof(lots));

out:
	fdrop(fp, td);
	return (error);
}