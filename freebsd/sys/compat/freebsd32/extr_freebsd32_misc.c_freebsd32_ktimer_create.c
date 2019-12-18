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
struct sigevent32 {int dummy; } ;
struct sigevent {int dummy; } ;
struct freebsd32_ktimer_create_args {int /*<<< orphan*/  timerid; int /*<<< orphan*/  clock_id; int /*<<< orphan*/ * evp; } ;
typedef  int /*<<< orphan*/  ev32 ;

/* Variables and functions */
 int convert_sigevent32 (struct sigevent32*,struct sigevent*) ; 
 int copyin (int /*<<< orphan*/ *,struct sigevent32*,int) ; 
 int copyout (int*,int /*<<< orphan*/ ,int) ; 
 int kern_ktimer_create (struct thread*,int /*<<< orphan*/ ,struct sigevent*,int*,int) ; 
 int /*<<< orphan*/  kern_ktimer_delete (struct thread*,int) ; 

int freebsd32_ktimer_create(struct thread *td,
    struct freebsd32_ktimer_create_args *uap)
{
	struct sigevent32 ev32;
	struct sigevent ev, *evp;
	int error, id;

	if (uap->evp == NULL) {
		evp = NULL;
	} else {
		evp = &ev;
		error = copyin(uap->evp, &ev32, sizeof(ev32));
		if (error != 0)
			return (error);
		error = convert_sigevent32(&ev32, &ev);
		if (error != 0)
			return (error);
	}
	error = kern_ktimer_create(td, uap->clock_id, evp, &id, -1);
	if (error == 0) {
		error = copyout(&id, uap->timerid, sizeof(int));
		if (error != 0)
			kern_ktimer_delete(td, id);
	}
	return (error);
}