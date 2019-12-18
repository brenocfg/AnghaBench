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
union sigval {int /*<<< orphan*/  sival_ptr; } ;
struct thread {int dummy; } ;
struct sigqueue_args {int /*<<< orphan*/  signum; int /*<<< orphan*/  pid; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int kern_sigqueue (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union sigval*) ; 

int
sys_sigqueue(struct thread *td, struct sigqueue_args *uap)
{
	union sigval sv;

	sv.sival_ptr = uap->value;

	return (kern_sigqueue(td, uap->pid, uap->signum, &sv));
}