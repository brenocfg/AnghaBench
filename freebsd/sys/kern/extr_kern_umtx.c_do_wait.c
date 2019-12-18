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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_long ;
struct umtx_q {int uq_flags; int /*<<< orphan*/  uq_key; } ;
struct thread {struct umtx_q* td_umtxq; } ;
struct abs_timeout {int dummy; } ;
struct _umtx_time {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_SHARE ; 
 int EFAULT ; 
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  THREAD_SHARE ; 
 int /*<<< orphan*/  TYPE_SIMPLE_WAIT ; 
 int UQF_UMTXQ ; 
 int /*<<< orphan*/  abs_timeout_init2 (struct abs_timeout*,struct _umtx_time*) ; 
 int fueword (void*,scalar_t__*) ; 
 int fueword32 (void*,scalar_t__*) ; 
 int umtx_key_get (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_key_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_insert (struct umtx_q*) ; 
 int /*<<< orphan*/  umtxq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_remove (struct umtx_q*) ; 
 int umtxq_sleep (struct umtx_q*,char*,struct abs_timeout*) ; 
 int /*<<< orphan*/  umtxq_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
do_wait(struct thread *td, void *addr, u_long id,
    struct _umtx_time *timeout, int compat32, int is_private)
{
	struct abs_timeout timo;
	struct umtx_q *uq;
	u_long tmp;
	uint32_t tmp32;
	int error = 0;

	uq = td->td_umtxq;
	if ((error = umtx_key_get(addr, TYPE_SIMPLE_WAIT,
		is_private ? THREAD_SHARE : AUTO_SHARE, &uq->uq_key)) != 0)
		return (error);

	if (timeout != NULL)
		abs_timeout_init2(&timo, timeout);

	umtxq_lock(&uq->uq_key);
	umtxq_insert(uq);
	umtxq_unlock(&uq->uq_key);
	if (compat32 == 0) {
		error = fueword(addr, &tmp);
		if (error != 0)
			error = EFAULT;
	} else {
		error = fueword32(addr, &tmp32);
		if (error == 0)
			tmp = tmp32;
		else
			error = EFAULT;
	}
	umtxq_lock(&uq->uq_key);
	if (error == 0) {
		if (tmp == id)
			error = umtxq_sleep(uq, "uwait", timeout == NULL ?
			    NULL : &timo);
		if ((uq->uq_flags & UQF_UMTXQ) == 0)
			error = 0;
		else
			umtxq_remove(uq);
	} else if ((uq->uq_flags & UQF_UMTXQ) != 0) {
		umtxq_remove(uq);
	}
	umtxq_unlock(&uq->uq_key);
	umtx_key_release(&uq->uq_key);
	if (error == ERESTART)
		error = EINTR;
	return (error);
}