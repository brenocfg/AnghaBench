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
struct ksem_close_args {int /*<<< orphan*/  id; } ;
struct ksem {int ks_flags; } ;
struct file {struct ksem* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int KS_ANONYMOUS ; 
 int /*<<< orphan*/  cap_no_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int kern_close (struct thread*,int /*<<< orphan*/ ) ; 
 int ksem_get (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**) ; 

int
sys_ksem_close(struct thread *td, struct ksem_close_args *uap)
{
	struct ksem *ks;
	struct file *fp;
	int error;

	/* No capability rights required to close a semaphore. */
	AUDIT_ARG_FD(uap->id);
	error = ksem_get(td, uap->id, &cap_no_rights, &fp);
	if (error)
		return (error);
	ks = fp->f_data;
	if (ks->ks_flags & KS_ANONYMOUS) {
		fdrop(fp, td);
		return (EINVAL);
	}
	error = kern_close(td, uap->id);
	fdrop(fp, td);
	return (error);
}