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
struct thread {int dummy; } ;
struct linux_timer_gettime_args {int /*<<< orphan*/  setting; int /*<<< orphan*/  timerid; } ;
struct l_itimerspec {int dummy; } ;
struct itimerspec {int dummy; } ;
typedef  int /*<<< orphan*/  l_val ;

/* Variables and functions */
 int /*<<< orphan*/  ITS_CP (struct itimerspec,struct l_itimerspec) ; 
 int copyout (struct l_itimerspec*,int /*<<< orphan*/ ,int) ; 
 int kern_ktimer_gettime (struct thread*,int /*<<< orphan*/ ,struct itimerspec*) ; 

int
linux_timer_gettime(struct thread *td, struct linux_timer_gettime_args *uap)
{
	struct l_itimerspec l_val;
	struct itimerspec val;
	int error;

	error = kern_ktimer_gettime(td, uap->timerid, &val);
	if (error == 0) {
		ITS_CP(val, l_val);
		error = copyout(&l_val, uap->setting, sizeof(l_val));
	}
	return (error);
}