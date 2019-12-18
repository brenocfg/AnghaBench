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
struct sigevent {int dummy; } ;
struct linux_timer_create_args {int /*<<< orphan*/  timerid; int /*<<< orphan*/  clock_id; int /*<<< orphan*/ * evp; } ;
struct l_sigevent {int dummy; } ;
typedef  int /*<<< orphan*/  l_ev ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int copyin (int /*<<< orphan*/ *,struct l_sigevent*,int) ; 
 int copyout (int*,int /*<<< orphan*/ ,int) ; 
 int kern_ktimer_create (struct thread*,int /*<<< orphan*/ ,struct sigevent*,int*,int) ; 
 int /*<<< orphan*/  kern_ktimer_delete (struct thread*,int) ; 
 int linux_convert_l_sigevent (struct l_sigevent*,struct sigevent*) ; 
 int linux_to_native_clockid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
linux_timer_create(struct thread *td, struct linux_timer_create_args *uap)
{
	struct l_sigevent l_ev;
	struct sigevent ev, *evp;
	clockid_t nwhich;
	int error, id;

	if (uap->evp == NULL) {
		evp = NULL;
	} else {
		error = copyin(uap->evp, &l_ev, sizeof(l_ev));
		if (error != 0)
			return (error);
		error = linux_convert_l_sigevent(&l_ev, &ev);
		if (error != 0)
			return (error);
		evp = &ev;
	}
	error = linux_to_native_clockid(&nwhich, uap->clock_id);
	if (error != 0)
		return (error);
	error = kern_ktimer_create(td, nwhich, evp, &id, -1);
	if (error == 0) {
		error = copyout(&id, uap->timerid, sizeof(int));
		if (error != 0)
			kern_ktimer_delete(td, id);
	}
	return (error);
}