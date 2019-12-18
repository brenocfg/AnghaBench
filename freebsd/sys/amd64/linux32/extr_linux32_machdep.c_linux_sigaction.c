#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct linux_sigaction_args {int /*<<< orphan*/ * osa; int /*<<< orphan*/ * nsa; int /*<<< orphan*/  sig; } ;
struct TYPE_10__ {int /*<<< orphan*/  __mask; } ;
struct TYPE_8__ {TYPE_7__ lsa_mask; int /*<<< orphan*/  lsa_restorer; int /*<<< orphan*/  lsa_flags; int /*<<< orphan*/  lsa_handler; } ;
typedef  TYPE_1__ l_sigaction_t ;
struct TYPE_9__ {int /*<<< orphan*/  lsa_mask; int /*<<< orphan*/  lsa_restorer; int /*<<< orphan*/  lsa_flags; int /*<<< orphan*/  lsa_handler; } ;
typedef  TYPE_2__ l_osigaction_t ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_SIGEMPTYSET (TYPE_7__) ; 
 int copyin (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int copyout (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int linux_do_sigaction (struct thread*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 

int
linux_sigaction(struct thread *td, struct linux_sigaction_args *args)
{
	l_osigaction_t osa;
	l_sigaction_t act, oact;
	int error;

	if (args->nsa != NULL) {
		error = copyin(args->nsa, &osa, sizeof(l_osigaction_t));
		if (error)
			return (error);
		act.lsa_handler = osa.lsa_handler;
		act.lsa_flags = osa.lsa_flags;
		act.lsa_restorer = osa.lsa_restorer;
		LINUX_SIGEMPTYSET(act.lsa_mask);
		act.lsa_mask.__mask = osa.lsa_mask;
	}

	error = linux_do_sigaction(td, args->sig, args->nsa ? &act : NULL,
	    args->osa ? &oact : NULL);

	if (args->osa != NULL && !error) {
		osa.lsa_handler = oact.lsa_handler;
		osa.lsa_flags = oact.lsa_flags;
		osa.lsa_restorer = oact.lsa_restorer;
		osa.lsa_mask = oact.lsa_mask.__mask;
		error = copyout(&osa, args->osa, sizeof(l_osigaction_t));
	}

	return (error);
}