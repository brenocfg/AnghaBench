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
struct clock_gettime_args {int /*<<< orphan*/  tp; int /*<<< orphan*/  clock_id; } ;
typedef  int /*<<< orphan*/  ats ;

/* Variables and functions */
 int copyout (struct timespec*,int /*<<< orphan*/ ,int) ; 
 int kern_clock_gettime (struct thread*,int /*<<< orphan*/ ,struct timespec*) ; 

int
sys_clock_gettime(struct thread *td, struct clock_gettime_args *uap)
{
	struct timespec ats;
	int error;

	error = kern_clock_gettime(td, uap->clock_id, &ats);
	if (error == 0)
		error = copyout(&ats, uap->tp, sizeof(ats));

	return (error);
}