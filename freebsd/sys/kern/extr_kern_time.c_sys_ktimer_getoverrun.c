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
struct ktimer_getoverrun_args {int /*<<< orphan*/  timerid; } ;

/* Variables and functions */
 int kern_ktimer_getoverrun (struct thread*,int /*<<< orphan*/ ) ; 

int
sys_ktimer_getoverrun(struct thread *td, struct ktimer_getoverrun_args *uap)
{

	return (kern_ktimer_getoverrun(td, uap->timerid));
}