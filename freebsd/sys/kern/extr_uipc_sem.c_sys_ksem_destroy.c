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
struct ksem_destroy_args {int /*<<< orphan*/  id; } ;
struct ksem {int ks_flags; scalar_t__ ks_waiters; } ;
struct file {struct ksem* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int KS_ANONYMOUS ; 
 int KS_DEAD ; 
 int /*<<< orphan*/  cap_no_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int kern_close (struct thread*,int /*<<< orphan*/ ) ; 
 int ksem_get (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_lock ; 

int
sys_ksem_destroy(struct thread *td, struct ksem_destroy_args *uap)
{
	struct file *fp;
	struct ksem *ks;
	int error;

	/* No capability rights required to close a semaphore. */
	AUDIT_ARG_FD(uap->id);
	error = ksem_get(td, uap->id, &cap_no_rights, &fp);
	if (error)
		return (error);
	ks = fp->f_data;
	if (!(ks->ks_flags & KS_ANONYMOUS)) {
		fdrop(fp, td);
		return (EINVAL);
	}
	mtx_lock(&sem_lock);
	if (ks->ks_waiters != 0) {
		mtx_unlock(&sem_lock);
		error = EBUSY;
		goto err;
	}
	ks->ks_flags |= KS_DEAD;
	mtx_unlock(&sem_lock);

	error = kern_close(td, uap->id);
err:
	fdrop(fp, td);
	return (error);
}