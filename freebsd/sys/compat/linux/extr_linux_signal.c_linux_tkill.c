#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_2__* td_proc; } ;
struct linux_tkill_args {scalar_t__ tid; int /*<<< orphan*/  sig; } ;
struct TYPE_8__ {int ksi_signo; int /*<<< orphan*/  ksi_uid; int /*<<< orphan*/  ksi_pid; scalar_t__ ksi_errno; int /*<<< orphan*/  ksi_code; } ;
typedef  TYPE_3__ ksiginfo_t ;
struct TYPE_7__ {TYPE_1__* p_ucred; int /*<<< orphan*/  p_pid; } ;
struct TYPE_6__ {int /*<<< orphan*/  cr_ruid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  LINUX_SIG_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_LWP ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_3__*) ; 
 int linux_do_tkill (struct thread*,struct thread*,TYPE_3__*) ; 
 struct thread* linux_tdfind (struct thread*,scalar_t__,int) ; 
 int linux_to_bsd_signal (int /*<<< orphan*/ ) ; 

int
linux_tkill(struct thread *td, struct linux_tkill_args *args)
{
	struct thread *tdt;
	ksiginfo_t ksi;
	int sig;

	if (args->tid <= 0)
		return (EINVAL);

	if (!LINUX_SIG_VALID(args->sig))
		return (EINVAL);

	sig = linux_to_bsd_signal(args->sig);

	tdt = linux_tdfind(td, args->tid, -1);
	if (tdt == NULL)
		return (ESRCH);

	ksiginfo_init(&ksi);
	ksi.ksi_signo = sig;
	ksi.ksi_code = SI_LWP;
	ksi.ksi_errno = 0;
	ksi.ksi_pid = td->td_proc->p_pid;
	ksi.ksi_uid = td->td_proc->p_ucred->cr_ruid;
	return (linux_do_tkill(td, tdt, &ksi));
}