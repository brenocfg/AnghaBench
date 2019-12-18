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
struct timeval {int tv_sec; int tv_usec; } ;
struct itimerval {struct timeval const it_interval; struct timeval const it_value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/  (*) ()) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ is_timeval_eq (struct timeval const*,struct timeval const*) ; 
 scalar_t__ one_shot ; 
 int start_timer_thread () ; 
 int /*<<< orphan*/  stop_timer_thread () ; 
 int timer_interval ; 
 scalar_t__ timer_thread ; 

int setitimer(int type, struct itimerval *in, struct itimerval *out)
{
	static const struct timeval zero;
	static int atexit_done;

	if (out != NULL)
		return errno = EINVAL,
			error("setitimer param 3 != NULL not implemented");
	if (!is_timeval_eq(&in->it_interval, &zero) &&
	    !is_timeval_eq(&in->it_interval, &in->it_value))
		return errno = EINVAL,
			error("setitimer: it_interval must be zero or eq it_value");

	if (timer_thread)
		stop_timer_thread();

	if (is_timeval_eq(&in->it_value, &zero) &&
	    is_timeval_eq(&in->it_interval, &zero))
		return 0;

	timer_interval = in->it_value.tv_sec * 1000 + in->it_value.tv_usec / 1000;
	one_shot = is_timeval_eq(&in->it_interval, &zero);
	if (!atexit_done) {
		atexit(stop_timer_thread);
		atexit_done = 1;
	}
	return start_timer_thread();
}