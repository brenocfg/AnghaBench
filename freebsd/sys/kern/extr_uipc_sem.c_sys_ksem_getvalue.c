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
typedef  int /*<<< orphan*/  val ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct ksem_getvalue_args {int /*<<< orphan*/  val; int /*<<< orphan*/  id; } ;
struct ksem {int ks_value; int /*<<< orphan*/  ks_atime; } ;
struct file {int /*<<< orphan*/  f_cred; struct ksem* f_data; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAP_SEM_GETVALUE ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int copyout (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int ksem_get (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file**) ; 
 int mac_posixsem_check_getvalue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ksem*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_lock ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 

int
sys_ksem_getvalue(struct thread *td, struct ksem_getvalue_args *uap)
{
	cap_rights_t rights;
	struct file *fp;
	struct ksem *ks;
	int error, val;

	AUDIT_ARG_FD(uap->id);
	error = ksem_get(td, uap->id,
	    cap_rights_init(&rights, CAP_SEM_GETVALUE), &fp);
	if (error)
		return (error);
	ks = fp->f_data;

	mtx_lock(&sem_lock);
#ifdef MAC
	error = mac_posixsem_check_getvalue(td->td_ucred, fp->f_cred, ks);
	if (error) {
		mtx_unlock(&sem_lock);
		fdrop(fp, td);
		return (error);
	}
#endif
	val = ks->ks_value;
	vfs_timestamp(&ks->ks_atime);
	mtx_unlock(&sem_lock);
	fdrop(fp, td);
	error = copyout(&val, uap->val, sizeof(val));
	return (error);
}