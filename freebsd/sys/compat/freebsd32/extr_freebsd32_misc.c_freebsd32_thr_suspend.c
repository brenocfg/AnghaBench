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
struct timespec32 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct thread {int dummy; } ;
struct freebsd32_thr_suspend_args {int /*<<< orphan*/ * timeout; } ;

/* Variables and functions */
 int copyin (void const*,void*,int) ; 
 int kern_thr_suspend (struct thread*,struct timespec*) ; 

int
freebsd32_thr_suspend(struct thread *td, struct freebsd32_thr_suspend_args *uap)
{
	struct timespec32 ts32;
	struct timespec ts, *tsp;
	int error;

	error = 0;
	tsp = NULL;
	if (uap->timeout != NULL) {
		error = copyin((const void *)uap->timeout, (void *)&ts32,
		    sizeof(struct timespec32));
		if (error != 0)
			return (error);
		ts.tv_sec = ts32.tv_sec;
		ts.tv_nsec = ts32.tv_nsec;
		tsp = &ts;
	}
	return (kern_thr_suspend(td, tsp));
}