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
typedef  int uint32_t ;
struct umutex {int /*<<< orphan*/  m_flags; } ;
struct thread {int dummy; } ;
struct _umtx_time {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINTR ; 
 int EINVAL ; 
 int ERESTART ; 
#define  UMUTEX_PRIO_INHERIT 129 
#define  UMUTEX_PRIO_PROTECT 128 
 int _UMUTEX_WAIT ; 
 int do_lock_normal (struct thread*,struct umutex*,int,struct _umtx_time*,int) ; 
 int do_lock_pi (struct thread*,struct umutex*,int,struct _umtx_time*,int) ; 
 int do_lock_pp (struct thread*,struct umutex*,int,struct _umtx_time*,int) ; 
 int fueword32 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
do_lock_umutex(struct thread *td, struct umutex *m,
    struct _umtx_time *timeout, int mode)
{
	uint32_t flags;
	int error;

	error = fueword32(&m->m_flags, &flags);
	if (error == -1)
		return (EFAULT);

	switch (flags & (UMUTEX_PRIO_INHERIT | UMUTEX_PRIO_PROTECT)) {
	case 0:
		error = do_lock_normal(td, m, flags, timeout, mode);
		break;
	case UMUTEX_PRIO_INHERIT:
		error = do_lock_pi(td, m, flags, timeout, mode);
		break;
	case UMUTEX_PRIO_PROTECT:
		error = do_lock_pp(td, m, flags, timeout, mode);
		break;
	default:
		return (EINVAL);
	}
	if (timeout == NULL) {
		if (error == EINTR && mode != _UMUTEX_WAIT)
			error = ERESTART;
	} else {
		/* Timed-locking is not restarted. */
		if (error == ERESTART)
			error = EINTR;
	}
	return (error);
}