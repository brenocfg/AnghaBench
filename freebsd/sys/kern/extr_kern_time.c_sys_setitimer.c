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
struct setitimer_args {int /*<<< orphan*/ * oitv; int /*<<< orphan*/  which; int /*<<< orphan*/ * itv; } ;
struct itimerval {int dummy; } ;
struct getitimer_args {int dummy; } ;

/* Variables and functions */
 int copyin (int /*<<< orphan*/ *,struct itimerval*,int) ; 
 int copyout (struct itimerval*,int /*<<< orphan*/ *,int) ; 
 int kern_setitimer (struct thread*,int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 
 int sys_getitimer (struct thread*,struct getitimer_args*) ; 

int
sys_setitimer(struct thread *td, struct setitimer_args *uap)
{
	struct itimerval aitv, oitv;
	int error;

	if (uap->itv == NULL) {
		uap->itv = uap->oitv;
		return (sys_getitimer(td, (struct getitimer_args *)uap));
	}

	if ((error = copyin(uap->itv, &aitv, sizeof(struct itimerval))))
		return (error);
	error = kern_setitimer(td, uap->which, &aitv, &oitv);
	if (error != 0 || uap->oitv == NULL)
		return (error);
	return (copyout(&oitv, uap->oitv, sizeof(struct itimerval)));
}