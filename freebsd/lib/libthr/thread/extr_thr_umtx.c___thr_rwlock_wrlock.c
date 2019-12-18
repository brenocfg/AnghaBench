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
typedef  int /*<<< orphan*/  timeout ;
struct urwlock {int dummy; } ;
struct timespec {int dummy; } ;
struct _umtx_time {int /*<<< orphan*/  _clockid; int /*<<< orphan*/  _flags; struct timespec _timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  UMTX_ABSTIME ; 
 int /*<<< orphan*/  UMTX_OP_RW_WRLOCK ; 
 int _umtx_op_err (struct urwlock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct _umtx_time*) ; 

int
__thr_rwlock_wrlock(struct urwlock *rwlock, const struct timespec *tsp)
{
	struct _umtx_time timeout, *tm_p;
	size_t tm_size;

	if (tsp == NULL) {
		tm_p = NULL;
		tm_size = 0;
	} else {
		timeout._timeout = *tsp;
		timeout._flags = UMTX_ABSTIME;
		timeout._clockid = CLOCK_REALTIME;
		tm_p = &timeout;
		tm_size = sizeof(timeout);
	}
	return (_umtx_op_err(rwlock, UMTX_OP_RW_WRLOCK, 0, (void *)tm_size,
	    tm_p));
}