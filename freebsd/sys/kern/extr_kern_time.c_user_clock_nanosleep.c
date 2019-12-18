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
typedef  int /*<<< orphan*/  rqt ;
typedef  int /*<<< orphan*/  rmt ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINTR ; 
 int TIMER_ABSTIME ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int copyin (struct timespec const*,struct timespec*,int) ; 
 int copyout (struct timespec*,struct timespec*,int) ; 
 int kern_clock_nanosleep (struct thread*,int /*<<< orphan*/ ,int,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  useracc (struct timespec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
user_clock_nanosleep(struct thread *td, clockid_t clock_id, int flags,
    const struct timespec *ua_rqtp, struct timespec *ua_rmtp)
{
	struct timespec rmt, rqt;
	int error;

	error = copyin(ua_rqtp, &rqt, sizeof(rqt));
	if (error)
		return (error);
	if (ua_rmtp != NULL && (flags & TIMER_ABSTIME) == 0 &&
	    !useracc(ua_rmtp, sizeof(rmt), VM_PROT_WRITE))
		return (EFAULT);
	error = kern_clock_nanosleep(td, clock_id, flags, &rqt, &rmt);
	if (error == EINTR && ua_rmtp != NULL && (flags & TIMER_ABSTIME) == 0) {
		int error2;

		error2 = copyout(&rmt, ua_rmtp, sizeof(rmt));
		if (error2)
			error = error2;
	}
	return (error);
}