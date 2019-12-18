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
struct timezone {int dummy; } ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PRIV_SETTIMEOFDAY ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int settime (struct thread*,struct timeval*) ; 

int
kern_settimeofday(struct thread *td, struct timeval *tv, struct timezone *tzp)
{
	int error;

	error = priv_check(td, PRIV_SETTIMEOFDAY);
	if (error)
		return (error);
	/* Verify all parameters before changing time. */
	if (tv) {
		if (tv->tv_usec < 0 || tv->tv_usec >= 1000000 ||
		    tv->tv_sec < 0)
			return (EINVAL);
		error = settime(td, tv);
	}
	return (error);
}