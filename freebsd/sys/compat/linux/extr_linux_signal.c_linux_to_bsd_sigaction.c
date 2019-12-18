#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_mask; } ;
struct TYPE_3__ {int lsa_flags; int /*<<< orphan*/  lsa_handler; int /*<<< orphan*/  lsa_mask; } ;
typedef  TYPE_1__ l_sigaction_t ;

/* Variables and functions */
 int LINUX_SA_NOCLDSTOP ; 
 int LINUX_SA_NOCLDWAIT ; 
 int LINUX_SA_NOMASK ; 
 int LINUX_SA_ONESHOT ; 
 int LINUX_SA_ONSTACK ; 
 int LINUX_SA_RESTART ; 
 int LINUX_SA_SIGINFO ; 
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_NOCLDSTOP ; 
 int /*<<< orphan*/  SA_NOCLDWAIT ; 
 int /*<<< orphan*/  SA_NODEFER ; 
 int /*<<< orphan*/  SA_ONSTACK ; 
 int /*<<< orphan*/  SA_RESETHAND ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  linux_to_bsd_sigset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
linux_to_bsd_sigaction(l_sigaction_t *lsa, struct sigaction *bsa)
{

	linux_to_bsd_sigset(&lsa->lsa_mask, &bsa->sa_mask);
	bsa->sa_handler = PTRIN(lsa->lsa_handler);
	bsa->sa_flags = 0;
	if (lsa->lsa_flags & LINUX_SA_NOCLDSTOP)
		bsa->sa_flags |= SA_NOCLDSTOP;
	if (lsa->lsa_flags & LINUX_SA_NOCLDWAIT)
		bsa->sa_flags |= SA_NOCLDWAIT;
	if (lsa->lsa_flags & LINUX_SA_SIGINFO)
		bsa->sa_flags |= SA_SIGINFO;
	if (lsa->lsa_flags & LINUX_SA_ONSTACK)
		bsa->sa_flags |= SA_ONSTACK;
	if (lsa->lsa_flags & LINUX_SA_RESTART)
		bsa->sa_flags |= SA_RESTART;
	if (lsa->lsa_flags & LINUX_SA_ONESHOT)
		bsa->sa_flags |= SA_RESETHAND;
	if (lsa->lsa_flags & LINUX_SA_NOMASK)
		bsa->sa_flags |= SA_NODEFER;
}