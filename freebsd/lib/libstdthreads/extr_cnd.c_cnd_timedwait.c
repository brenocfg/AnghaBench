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
typedef  int /*<<< orphan*/  mtx_t ;
typedef  int /*<<< orphan*/  cnd_t ;

/* Variables and functions */
#define  ETIMEDOUT 128 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*) ; 
 int thrd_error ; 
 int thrd_success ; 
 int thrd_timedout ; 

int
cnd_timedwait(cnd_t *restrict cond, mtx_t *restrict mtx,
    const struct timespec *restrict ts)
{

	switch (pthread_cond_timedwait(cond, mtx, ts)) {
	case 0:
		return (thrd_success);
	case ETIMEDOUT:
		return (thrd_timedout);
	default:
		return (thrd_error);
	}
}