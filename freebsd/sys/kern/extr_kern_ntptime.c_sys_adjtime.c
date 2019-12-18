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
struct timeval {int dummy; } ;
struct thread {int dummy; } ;
struct adjtime_args {int /*<<< orphan*/  olddelta; scalar_t__ delta; } ;
typedef  int /*<<< orphan*/  olddelta ;
typedef  int /*<<< orphan*/  delta ;

/* Variables and functions */
 int copyin (scalar_t__,struct timeval*,int) ; 
 int copyout (struct timeval*,int /*<<< orphan*/ ,int) ; 
 int kern_adjtime (struct thread*,struct timeval*,struct timeval*) ; 

int
sys_adjtime(struct thread *td, struct adjtime_args *uap)
{
	struct timeval delta, olddelta, *deltap;
	int error;

	if (uap->delta) {
		error = copyin(uap->delta, &delta, sizeof(delta));
		if (error)
			return (error);
		deltap = &delta;
	} else
		deltap = NULL;
	error = kern_adjtime(td, deltap, &olddelta);
	if (uap->olddelta && error == 0)
		error = copyout(&olddelta, uap->olddelta, sizeof(olddelta));
	return (error);
}