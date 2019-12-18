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
struct sigaction {uintptr_t sa_handler; int sa_flags; int /*<<< orphan*/  sa_mask; } ;
struct TYPE_3__ {uintptr_t lsa_handler; int /*<<< orphan*/  lsa_flags; scalar_t__ lsa_restorer; int /*<<< orphan*/  lsa_mask; } ;
typedef  TYPE_1__ l_sigaction_t ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_SA_NOCLDSTOP ; 
 int /*<<< orphan*/  LINUX_SA_NOCLDWAIT ; 
 int /*<<< orphan*/  LINUX_SA_NOMASK ; 
 int /*<<< orphan*/  LINUX_SA_ONESHOT ; 
 int /*<<< orphan*/  LINUX_SA_ONSTACK ; 
 int /*<<< orphan*/  LINUX_SA_RESTART ; 
 int /*<<< orphan*/  LINUX_SA_SIGINFO ; 
 int SA_NOCLDSTOP ; 
 int SA_NOCLDWAIT ; 
 int SA_NODEFER ; 
 int SA_ONSTACK ; 
 int SA_RESETHAND ; 
 int SA_RESTART ; 
 int SA_SIGINFO ; 
 int /*<<< orphan*/  bsd_to_linux_sigset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bsd_to_linux_sigaction(struct sigaction *bsa, l_sigaction_t *lsa)
{

	bsd_to_linux_sigset(&bsa->sa_mask, &lsa->lsa_mask);
#ifdef COMPAT_LINUX32
	lsa->lsa_handler = (uintptr_t)bsa->sa_handler;
#else
	lsa->lsa_handler = bsa->sa_handler;
#endif
	lsa->lsa_restorer = 0;		/* unsupported */
	lsa->lsa_flags = 0;
	if (bsa->sa_flags & SA_NOCLDSTOP)
		lsa->lsa_flags |= LINUX_SA_NOCLDSTOP;
	if (bsa->sa_flags & SA_NOCLDWAIT)
		lsa->lsa_flags |= LINUX_SA_NOCLDWAIT;
	if (bsa->sa_flags & SA_SIGINFO)
		lsa->lsa_flags |= LINUX_SA_SIGINFO;
	if (bsa->sa_flags & SA_ONSTACK)
		lsa->lsa_flags |= LINUX_SA_ONSTACK;
	if (bsa->sa_flags & SA_RESTART)
		lsa->lsa_flags |= LINUX_SA_RESTART;
	if (bsa->sa_flags & SA_RESETHAND)
		lsa->lsa_flags |= LINUX_SA_ONESHOT;
	if (bsa->sa_flags & SA_NODEFER)
		lsa->lsa_flags |= LINUX_SA_NOMASK;
}