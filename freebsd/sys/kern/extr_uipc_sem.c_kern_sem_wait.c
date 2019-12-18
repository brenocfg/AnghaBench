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
struct timeval {scalar_t__ tv_sec; } ;
struct timespec {int dummy; } ;
struct thread {TYPE_1__* td_proc; int /*<<< orphan*/  td_ucred; } ;
struct ksem {scalar_t__ ks_value; int /*<<< orphan*/  ks_waiters; int /*<<< orphan*/  ks_cv; int /*<<< orphan*/  ks_atime; } ;
struct file {int /*<<< orphan*/  f_cred; struct ksem* f_data; } ;
typedef  int /*<<< orphan*/  semid_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_2__ {scalar_t__ p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAP_SEM_WAIT ; 
 int /*<<< orphan*/  DP (char*) ; 
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cv_timedwait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int ksem_get (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file**) ; 
 int mac_posixsem_check_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ksem*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_lock ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  tvtohz (struct timeval*) ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kern_sem_wait(struct thread *td, semid_t id, int tryflag,
    struct timespec *abstime)
{
	struct timespec ts1, ts2;
	struct timeval tv;
	cap_rights_t rights;
	struct file *fp;
	struct ksem *ks;
	int error;

	DP((">>> kern_sem_wait entered! pid=%d\n", (int)td->td_proc->p_pid));
	AUDIT_ARG_FD(id);
	error = ksem_get(td, id, cap_rights_init(&rights, CAP_SEM_WAIT), &fp);
	if (error)
		return (error);
	ks = fp->f_data;
	mtx_lock(&sem_lock);
	DP((">>> kern_sem_wait critical section entered! pid=%d\n",
	    (int)td->td_proc->p_pid));
#ifdef MAC
	error = mac_posixsem_check_wait(td->td_ucred, fp->f_cred, ks);
	if (error) {
		DP(("kern_sem_wait mac failed\n"));
		goto err;
	}
#endif
	DP(("kern_sem_wait value = %d, tryflag %d\n", ks->ks_value, tryflag));
	vfs_timestamp(&ks->ks_atime);
	while (ks->ks_value == 0) {
		ks->ks_waiters++;
		if (tryflag != 0)
			error = EAGAIN;
		else if (abstime == NULL)
			error = cv_wait_sig(&ks->ks_cv, &sem_lock);
		else {
			for (;;) {
				ts1 = *abstime;
				getnanotime(&ts2);
				timespecsub(&ts1, &ts2, &ts1);
				TIMESPEC_TO_TIMEVAL(&tv, &ts1);
				if (tv.tv_sec < 0) {
					error = ETIMEDOUT;
					break;
				}
				error = cv_timedwait_sig(&ks->ks_cv,
				    &sem_lock, tvtohz(&tv));
				if (error != EWOULDBLOCK)
					break;
			}
		}
		ks->ks_waiters--;
		if (error)
			goto err;
	}
	ks->ks_value--;
	DP(("kern_sem_wait value post-decrement = %d\n", ks->ks_value));
	error = 0;
err:
	mtx_unlock(&sem_lock);
	fdrop(fp, td);
	DP(("<<< kern_sem_wait leaving, pid=%d, error = %d\n",
	    (int)td->td_proc->p_pid, error));
	return (error);
}