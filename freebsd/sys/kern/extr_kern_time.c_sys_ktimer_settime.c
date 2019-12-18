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
typedef  int /*<<< orphan*/  val ;
struct thread {int dummy; } ;
struct ktimer_settime_args {int /*<<< orphan*/ * ovalue; int /*<<< orphan*/  flags; int /*<<< orphan*/  timerid; int /*<<< orphan*/  value; } ;
struct itimerspec {int dummy; } ;

/* Variables and functions */
 int copyin (int /*<<< orphan*/ ,struct itimerspec*,int) ; 
 int copyout (struct itimerspec*,int /*<<< orphan*/ *,int) ; 
 int kern_ktimer_settime (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,struct itimerspec*) ; 

int
sys_ktimer_settime(struct thread *td, struct ktimer_settime_args *uap)
{
	struct itimerspec val, oval, *ovalp;
	int error;

	error = copyin(uap->value, &val, sizeof(val));
	if (error != 0)
		return (error);
	ovalp = uap->ovalue != NULL ? &oval : NULL;
	error = kern_ktimer_settime(td, uap->timerid, uap->flags, &val, ovalp);
	if (error == 0 && uap->ovalue != NULL)
		error = copyout(ovalp, uap->ovalue, sizeof(*ovalp));
	return (error);
}