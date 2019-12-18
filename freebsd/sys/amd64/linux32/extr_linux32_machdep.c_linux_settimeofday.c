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
struct timezone {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct thread {int dummy; } ;
struct linux_settimeofday_args {scalar_t__ tzp; scalar_t__ tp; } ;
typedef  struct timezone l_timeval ;
typedef  int /*<<< orphan*/  atz ;
typedef  int /*<<< orphan*/  atv32 ;

/* Variables and functions */
 int copyin (scalar_t__,struct timezone*,int) ; 
 int kern_settimeofday (struct thread*,struct timeval*,struct timezone*) ; 

int
linux_settimeofday(struct thread *td, struct linux_settimeofday_args *uap)
{
	l_timeval atv32;
	struct timeval atv, *tvp;
	struct timezone atz, *tzp;
	int error;

	if (uap->tp) {
		error = copyin(uap->tp, &atv32, sizeof(atv32));
		if (error)
			return (error);
		atv.tv_sec = atv32.tv_sec;
		atv.tv_usec = atv32.tv_usec;
		tvp = &atv;
	} else
		tvp = NULL;
	if (uap->tzp) {
		error = copyin(uap->tzp, &atz, sizeof(atz));
		if (error)
			return (error);
		tzp = &atz;
	} else
		tzp = NULL;
	return (kern_settimeofday(td, tvp, tzp));
}