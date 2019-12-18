#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct linux_sigsuspend_args {int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_4__ {int /*<<< orphan*/  __mask; } ;
typedef  TYPE_1__ l_sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_SIGEMPTYSET (TYPE_1__) ; 
 int kern_sigsuspend (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_to_bsd_sigset (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
linux_sigsuspend(struct thread *td, struct linux_sigsuspend_args *args)
{
	sigset_t sigmask;
	l_sigset_t mask;

	LINUX_SIGEMPTYSET(mask);
	mask.__mask = args->mask;
	linux_to_bsd_sigset(&mask, &sigmask);
	return (kern_sigsuspend(td, sigmask));
}