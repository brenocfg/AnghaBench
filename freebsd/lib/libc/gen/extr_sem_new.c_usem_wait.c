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
typedef  int /*<<< orphan*/  tms ;
struct timespec {int dummy; } ;
struct _usem2 {int dummy; } ;
struct _umtx_time {struct timespec _timeout; int /*<<< orphan*/  _flags; int /*<<< orphan*/  _clockid; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int TIMER_ABSTIME ; 
 int /*<<< orphan*/  UMTX_ABSTIME ; 
 int /*<<< orphan*/  UMTX_OP_SEM2_WAIT ; 
 int _umtx_op (struct _usem2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 scalar_t__ errno ; 

__attribute__((used)) static __inline int
usem_wait(struct _usem2 *sem, clockid_t clock_id, int flags,
    const struct timespec *rqtp, struct timespec *rmtp)
{
	struct {
		struct _umtx_time timeout;
		struct timespec remain;
	} tms;
	void *tm_p;
	size_t tm_size;
	int retval;

	if (rqtp == NULL) {
		tm_p = NULL;
		tm_size = 0;
	} else {
		tms.timeout._clockid = clock_id;
		tms.timeout._flags = (flags & TIMER_ABSTIME) ? UMTX_ABSTIME : 0;
		tms.timeout._timeout = *rqtp;
		tm_p = &tms;
		tm_size = sizeof(tms);
	}
	retval = _umtx_op(sem, UMTX_OP_SEM2_WAIT, 0, (void *)tm_size, tm_p);
	if (retval == -1 && errno == EINTR && (flags & TIMER_ABSTIME) == 0 &&
	    rqtp != NULL && rmtp != NULL) {
		*rmtp = tms.remain;
	}

	return (retval);
}