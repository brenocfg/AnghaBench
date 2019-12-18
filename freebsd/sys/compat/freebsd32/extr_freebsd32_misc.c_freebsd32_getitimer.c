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
struct itimerval32 {int dummy; } ;
struct itimerval {int dummy; } ;
struct freebsd32_getitimer_args {int /*<<< orphan*/ * itv; int /*<<< orphan*/  which; } ;
typedef  int /*<<< orphan*/  i32 ;

/* Variables and functions */
 int /*<<< orphan*/  TV_CP (struct itimerval,struct itimerval32,int /*<<< orphan*/ ) ; 
 int copyout (struct itimerval32*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  it_interval ; 
 int /*<<< orphan*/  it_value ; 
 int kern_getitimer (struct thread*,int /*<<< orphan*/ ,struct itimerval*) ; 

int
freebsd32_getitimer(struct thread *td, struct freebsd32_getitimer_args *uap)
{
	struct itimerval itv;
	struct itimerval32 i32;
	int error;

	error = kern_getitimer(td, uap->which, &itv);
	if (error || uap->itv == NULL)
		return (error);
	TV_CP(itv, i32, it_interval);
	TV_CP(itv, i32, it_value);
	return (copyout(&i32, uap->itv, sizeof(i32)));
}