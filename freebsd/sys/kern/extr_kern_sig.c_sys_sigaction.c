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
struct sigaction_args {int /*<<< orphan*/ * oact; int /*<<< orphan*/  sig; int /*<<< orphan*/ * act; } ;
struct sigaction {int dummy; } ;
typedef  int /*<<< orphan*/  oact ;
typedef  int /*<<< orphan*/  act ;

/* Variables and functions */
 int copyin (int /*<<< orphan*/ *,struct sigaction*,int) ; 
 int copyout (struct sigaction*,int /*<<< orphan*/ *,int) ; 
 int kern_sigaction (struct thread*,int /*<<< orphan*/ ,struct sigaction*,struct sigaction*,int /*<<< orphan*/ ) ; 

int
sys_sigaction(struct thread *td, struct sigaction_args *uap)
{
	struct sigaction act, oact;
	struct sigaction *actp, *oactp;
	int error;

	actp = (uap->act != NULL) ? &act : NULL;
	oactp = (uap->oact != NULL) ? &oact : NULL;
	if (actp) {
		error = copyin(uap->act, actp, sizeof(act));
		if (error)
			return (error);
	}
	error = kern_sigaction(td, uap->sig, actp, oactp, 0);
	if (oactp && !error)
		error = copyout(oactp, uap->oact, sizeof(oact));
	return (error);
}