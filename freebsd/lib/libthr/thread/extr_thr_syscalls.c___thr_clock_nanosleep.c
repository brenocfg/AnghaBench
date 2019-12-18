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
struct pthread {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int __sys_clock_nanosleep (int /*<<< orphan*/ ,int,struct timespec const*,struct timespec*) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter (struct pthread*) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int) ; 

__attribute__((used)) static int
__thr_clock_nanosleep(clockid_t clock_id, int flags,
    const struct timespec *time_to_sleep, struct timespec *time_remaining)
{
	struct pthread *curthread;
	int ret;

	curthread = _get_curthread();
	_thr_cancel_enter(curthread);
	ret = __sys_clock_nanosleep(clock_id, flags, time_to_sleep,
	    time_remaining);
	_thr_cancel_leave(curthread, 1);

	return (ret);
}