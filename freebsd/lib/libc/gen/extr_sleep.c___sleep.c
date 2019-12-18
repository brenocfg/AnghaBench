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
typedef  struct timespec {unsigned int tv_sec; scalar_t__ tv_nsec; } const timespec ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 size_t INTERPOS_nanosleep ; 
 unsigned int INT_MAX ; 
 scalar_t__* __libc_interposing ; 
 scalar_t__ errno ; 
 int stub1 (struct timespec const*,struct timespec const*) ; 

unsigned int
__sleep(unsigned int seconds)
{
	struct timespec time_to_sleep;
	struct timespec time_remaining;

	/*
	 * Avoid overflow when `seconds' is huge.  This assumes that
	 * the maximum value for a time_t is >= INT_MAX.
	 */
	if (seconds > INT_MAX)
		return (seconds - INT_MAX + __sleep(INT_MAX));

	time_to_sleep.tv_sec = seconds;
	time_to_sleep.tv_nsec = 0;
	if (((int (*)(const struct timespec *, struct timespec *))
	    __libc_interposing[INTERPOS_nanosleep])(
	    &time_to_sleep, &time_remaining) != -1)
		return (0);
	if (errno != EINTR)
		return (seconds);		/* best guess */
	return (time_remaining.tv_sec +
	    (time_remaining.tv_nsec != 0)); /* round up */
}