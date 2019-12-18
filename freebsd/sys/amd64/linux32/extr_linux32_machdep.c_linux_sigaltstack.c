#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct linux_sigaltstack_args {int /*<<< orphan*/ * uoss; int /*<<< orphan*/ * uss; } ;
struct TYPE_7__ {int /*<<< orphan*/  ss_flags; int /*<<< orphan*/  ss_size; int /*<<< orphan*/  ss_sp; } ;
typedef  TYPE_1__ stack_t ;
struct TYPE_8__ {int /*<<< orphan*/  ss_flags; int /*<<< orphan*/  ss_size; int /*<<< orphan*/  ss_sp; } ;
typedef  TYPE_2__ l_stack_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTROUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsd_to_linux_sigaltstack (int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int copyout (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int kern_sigaltstack (struct thread*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  linux_to_bsd_sigaltstack (int /*<<< orphan*/ ) ; 

int
linux_sigaltstack(struct thread *td, struct linux_sigaltstack_args *uap)
{
	stack_t ss, oss;
	l_stack_t lss;
	int error;

	if (uap->uss != NULL) {
		error = copyin(uap->uss, &lss, sizeof(l_stack_t));
		if (error)
			return (error);

		ss.ss_sp = PTRIN(lss.ss_sp);
		ss.ss_size = lss.ss_size;
		ss.ss_flags = linux_to_bsd_sigaltstack(lss.ss_flags);
	}
	error = kern_sigaltstack(td, (uap->uss != NULL) ? &ss : NULL,
	    (uap->uoss != NULL) ? &oss : NULL);
	if (!error && uap->uoss != NULL) {
		lss.ss_sp = PTROUT(oss.ss_sp);
		lss.ss_size = oss.ss_size;
		lss.ss_flags = bsd_to_linux_sigaltstack(oss.ss_flags);
		error = copyout(&lss, uap->uoss, sizeof(l_stack_t));
	}

	return (error);
}