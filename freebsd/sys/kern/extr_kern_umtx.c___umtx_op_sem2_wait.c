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
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct _umtx_time {int _flags; int /*<<< orphan*/  _timeout; } ;
struct _umtx_op_args {int /*<<< orphan*/ * uaddr2; int /*<<< orphan*/  obj; scalar_t__ uaddr1; } ;

/* Variables and functions */
 int EINTR ; 
 int UMTX_ABSTIME ; 
 int copyout (int /*<<< orphan*/ *,struct _umtx_time*,int) ; 
 int do_sem2_wait (struct thread*,int /*<<< orphan*/ ,struct _umtx_time*) ; 
 int umtx_copyin_umtx_time (int /*<<< orphan*/ *,size_t,struct _umtx_time*) ; 

__attribute__((used)) static int
__umtx_op_sem2_wait(struct thread *td, struct _umtx_op_args *uap)
{
	struct _umtx_time *tm_p, timeout;
	size_t uasize;
	int error;

	/* Allow a null timespec (wait forever). */
	if (uap->uaddr2 == NULL) {
		uasize = 0;
		tm_p = NULL;
	} else {
		uasize = (size_t)uap->uaddr1;
		error = umtx_copyin_umtx_time(uap->uaddr2, uasize, &timeout);
		if (error != 0)
			return (error);
		tm_p = &timeout;
	}
	error = do_sem2_wait(td, uap->obj, tm_p);
	if (error == EINTR && uap->uaddr2 != NULL &&
	    (timeout._flags & UMTX_ABSTIME) == 0 &&
	    uasize >= sizeof(struct _umtx_time) + sizeof(struct timespec)) {
		error = copyout(&timeout._timeout,
		    (struct _umtx_time *)uap->uaddr2 + 1,
		    sizeof(struct timespec));
		if (error == 0) {
			error = EINTR;
		}
	}

	return (error);
}