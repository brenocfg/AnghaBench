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
struct timeval {int dummy; } ;
struct timespec {int dummy; } ;
struct itimerspec {struct timespec it_value; int /*<<< orphan*/  it_interval; } ;
struct timerfd {int tfd_canceled; int /*<<< orphan*/  tfd_lock; int /*<<< orphan*/  tfd_callout; struct itimerspec tfd_time; } ;
struct thread {int dummy; } ;
struct linux_timerfd_settime_args {int flags; int /*<<< orphan*/ * old_value; int /*<<< orphan*/  fd; int /*<<< orphan*/  new_value; } ;
struct l_itimerspec {int dummy; } ;
struct file {scalar_t__ f_type; struct timerfd* f_data; } ;
typedef  int /*<<< orphan*/  lots ;

/* Variables and functions */
 scalar_t__ DTYPE_LINUXTFD ; 
 int EINVAL ; 
 int LINUX_TFD_SETTIME_FLAGS ; 
 int LINUX_TFD_TIMER_ABSTIME ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timerfd*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_write_rights ; 
 int copyin (int /*<<< orphan*/ ,struct l_itimerspec*,int) ; 
 int copyout (struct l_itimerspec*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**) ; 
 int /*<<< orphan*/  linux_timerfd_clocktime (struct timerfd*,struct timespec*) ; 
 int /*<<< orphan*/  linux_timerfd_curval (struct timerfd*,struct itimerspec*) ; 
 int /*<<< orphan*/  linux_timerfd_expire ; 
 int linux_to_native_itimerspec (struct itimerspec*,struct l_itimerspec*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int native_to_linux_itimerspec (struct l_itimerspec*,struct itimerspec*) ; 
 int /*<<< orphan*/  timespecadd (struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  timespecclear (int /*<<< orphan*/ *) ; 
 scalar_t__ timespecisset (struct timespec*) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 

int
linux_timerfd_settime(struct thread *td, struct linux_timerfd_settime_args *args)
{
	struct l_itimerspec lots;
	struct itimerspec nts, ots;
	struct timespec cts, ts;
	struct timerfd *tfd;
	struct timeval tv;
	struct file *fp;
	int error;

	if ((args->flags & ~LINUX_TFD_SETTIME_FLAGS) != 0)
		return (EINVAL);

	error = copyin(args->new_value, &lots, sizeof(lots));
	if (error != 0)
		return (error);
	error = linux_to_native_itimerspec(&nts, &lots);
	if (error != 0)
		return (error);

	error = fget(td, args->fd, &cap_write_rights, &fp);
	if (error != 0)
		return (error);
	tfd = fp->f_data;
	if (fp->f_type != DTYPE_LINUXTFD || tfd == NULL) {
		error = EINVAL;
		goto out;
	}

	mtx_lock(&tfd->tfd_lock);
	if (!timespecisset(&nts.it_value))
		timespecclear(&nts.it_interval);
	if (args->old_value != NULL)
		linux_timerfd_curval(tfd, &ots);

	tfd->tfd_time = nts;
	if (timespecisset(&nts.it_value)) {
		linux_timerfd_clocktime(tfd, &cts);
		ts = nts.it_value;
		if ((args->flags & LINUX_TFD_TIMER_ABSTIME) == 0) {
			timespecadd(&tfd->tfd_time.it_value, &cts,
				&tfd->tfd_time.it_value);
		} else {
			timespecsub(&ts, &cts, &ts);
		}
		TIMESPEC_TO_TIMEVAL(&tv, &ts);
		callout_reset(&tfd->tfd_callout, tvtohz(&tv),
			linux_timerfd_expire, tfd);
		tfd->tfd_canceled = false;
	} else {
		tfd->tfd_canceled = true;
		callout_stop(&tfd->tfd_callout);
	}
	mtx_unlock(&tfd->tfd_lock);

	if (args->old_value != NULL) {
		error = native_to_linux_itimerspec(&lots, &ots);
		if (error == 0)
			error = copyout(&lots, args->old_value, sizeof(lots));
	}

out:
	fdrop(fp, td);
	return (error);
}