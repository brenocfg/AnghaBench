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
struct ksem_post_args {int /*<<< orphan*/  id; } ;
struct ksem {scalar_t__ ks_value; scalar_t__ ks_waiters; int /*<<< orphan*/  ks_ctime; int /*<<< orphan*/  ks_cv; } ;
struct file {int /*<<< orphan*/  f_cred; struct ksem* f_data; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAP_SEM_POST ; 
 int EOVERFLOW ; 
 scalar_t__ SEM_VALUE_MAX ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int ksem_get (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file**) ; 
 int mac_posixsem_check_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ksem*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_lock ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 

int
sys_ksem_post(struct thread *td, struct ksem_post_args *uap)
{
	cap_rights_t rights;
	struct file *fp;
	struct ksem *ks;
	int error;

	AUDIT_ARG_FD(uap->id);
	error = ksem_get(td, uap->id,
	    cap_rights_init(&rights, CAP_SEM_POST), &fp);
	if (error)
		return (error);
	ks = fp->f_data;

	mtx_lock(&sem_lock);
#ifdef MAC
	error = mac_posixsem_check_post(td->td_ucred, fp->f_cred, ks);
	if (error)
		goto err;
#endif
	if (ks->ks_value == SEM_VALUE_MAX) {
		error = EOVERFLOW;
		goto err;
	}
	++ks->ks_value;
	if (ks->ks_waiters > 0)
		cv_signal(&ks->ks_cv);
	error = 0;
	vfs_timestamp(&ks->ks_ctime);
err:
	mtx_unlock(&sem_lock);
	fdrop(fp, td);
	return (error);
}