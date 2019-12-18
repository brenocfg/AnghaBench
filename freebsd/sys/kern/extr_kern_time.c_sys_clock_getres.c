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
typedef  int /*<<< orphan*/  ts ;
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct clock_getres_args {int /*<<< orphan*/ * tp; int /*<<< orphan*/  clock_id; } ;

/* Variables and functions */
 int copyout (struct timespec*,int /*<<< orphan*/ *,int) ; 
 int kern_clock_getres (struct thread*,int /*<<< orphan*/ ,struct timespec*) ; 

int
sys_clock_getres(struct thread *td, struct clock_getres_args *uap)
{
	struct timespec ts;
	int error;

	if (uap->tp == NULL)
		return (0);

	error = kern_clock_getres(td, uap->clock_id, &ts);
	if (error == 0)
		error = copyout(&ts, uap->tp, sizeof(ts));
	return (error);
}