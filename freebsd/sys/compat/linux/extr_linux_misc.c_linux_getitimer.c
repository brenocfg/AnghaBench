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
struct linux_getitimer_args {int /*<<< orphan*/  itv; int /*<<< orphan*/  which; } ;
struct l_itimerval {int dummy; } ;
struct itimerval {int dummy; } ;
typedef  int /*<<< orphan*/  ls ;

/* Variables and functions */
 int /*<<< orphan*/  B2L_ITIMERVAL (struct l_itimerval*,struct itimerval*) ; 
 int copyout (struct l_itimerval*,int /*<<< orphan*/ ,int) ; 
 int kern_getitimer (struct thread*,int /*<<< orphan*/ ,struct itimerval*) ; 

int
linux_getitimer(struct thread *td, struct linux_getitimer_args *uap)
{
	int error;
	struct l_itimerval ls;
	struct itimerval aitv;

	error = kern_getitimer(td, uap->which, &aitv);
	if (error != 0)
		return (error);
	B2L_ITIMERVAL(&ls, &aitv);
	return (copyout(&ls, uap->itv, sizeof(ls)));
}