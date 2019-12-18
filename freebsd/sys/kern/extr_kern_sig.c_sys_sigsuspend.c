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
struct sigsuspend_args {int /*<<< orphan*/  sigmask; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  mask ;

/* Variables and functions */
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int kern_sigsuspend (struct thread*,int /*<<< orphan*/ ) ; 

int
sys_sigsuspend(struct thread *td, struct sigsuspend_args *uap)
{
	sigset_t mask;
	int error;

	error = copyin(uap->sigmask, &mask, sizeof(mask));
	if (error)
		return (error);
	return (kern_sigsuspend(td, mask));
}