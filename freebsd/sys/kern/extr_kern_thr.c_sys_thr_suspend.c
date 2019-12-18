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
struct thr_suspend_args {int /*<<< orphan*/ * timeout; } ;

/* Variables and functions */
 int kern_thr_suspend (struct thread*,struct timespec*) ; 
 int umtx_copyin_timeout (int /*<<< orphan*/ *,struct timespec*) ; 

int
sys_thr_suspend(struct thread *td, struct thr_suspend_args *uap)
	/* const struct timespec *timeout */
{
	struct timespec ts, *tsp;
	int error;

	tsp = NULL;
	if (uap->timeout != NULL) {
		error = umtx_copyin_timeout(uap->timeout, &ts);
		if (error != 0)
			return (error);
		tsp = &ts;
	}

	return (kern_thr_suspend(td, tsp));
}