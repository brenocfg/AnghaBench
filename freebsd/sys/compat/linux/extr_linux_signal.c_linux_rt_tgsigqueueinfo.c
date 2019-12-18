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
struct linux_rt_tgsigqueueinfo_args {int /*<<< orphan*/  sig; int /*<<< orphan*/  tgid; int /*<<< orphan*/  tid; int /*<<< orphan*/  uinfo; } ;
typedef  int /*<<< orphan*/  linfo ;
struct TYPE_4__ {scalar_t__ lsi_code; } ;
typedef  TYPE_1__ l_siginfo_t ;
typedef  int /*<<< orphan*/  ksiginfo_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  LINUX_SIG_VALID (int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ksiginfo_init (int /*<<< orphan*/ *) ; 
 int linux_do_tkill (struct thread*,struct thread*,int /*<<< orphan*/ *) ; 
 struct thread* linux_tdfind (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int linux_to_bsd_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsiginfo_to_ksiginfo (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int
linux_rt_tgsigqueueinfo(struct thread *td, struct linux_rt_tgsigqueueinfo_args *args)
{
	l_siginfo_t linfo;
	struct thread *tds;
	ksiginfo_t ksi;
	int error;
	int sig;

	if (!LINUX_SIG_VALID(args->sig))
		return (EINVAL);

	error = copyin(args->uinfo, &linfo, sizeof(linfo));
	if (error != 0)
		return (error);

	if (linfo.lsi_code >= 0)
		return (EPERM);

	tds = linux_tdfind(td, args->tid, args->tgid);
	if (tds == NULL)
		return (ESRCH);

	sig = linux_to_bsd_signal(args->sig);
	ksiginfo_init(&ksi);
	lsiginfo_to_ksiginfo(&linfo, &ksi, sig);
	return (linux_do_tkill(td, tds, &ksi));
}