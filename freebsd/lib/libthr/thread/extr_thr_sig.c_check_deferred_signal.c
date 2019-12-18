#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  uc_sigmask; } ;
typedef  TYPE_1__ ucontext_t ;
struct sigaction {int dummy; } ;
struct TYPE_11__ {scalar_t__ si_signo; } ;
struct pthread {int deferred_run; TYPE_4__ deferred_siginfo; int /*<<< orphan*/  deferred_sigmask; struct sigaction deferred_sigact; } ;
struct TYPE_10__ {int /*<<< orphan*/  si_signo; } ;
typedef  TYPE_2__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  __fillcontextx2 (char*) ; 
 int __getcontextx_size () ; 
 scalar_t__ __predict_true (int) ; 
 TYPE_1__* alloca (int) ; 
 int /*<<< orphan*/  getcontext (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_signal (struct sigaction*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_4__*,int) ; 

__attribute__((used)) static void
check_deferred_signal(struct pthread *curthread)
{
	ucontext_t *uc;
	struct sigaction act;
	siginfo_t info;
	int uc_len;

	if (__predict_true(curthread->deferred_siginfo.si_signo == 0 ||
	    curthread->deferred_run))
		return;

	curthread->deferred_run = 1;
	uc_len = __getcontextx_size();
	uc = alloca(uc_len);
	getcontext(uc);
	if (curthread->deferred_siginfo.si_signo == 0) {
		curthread->deferred_run = 0;
		return;
	}
	__fillcontextx2((char *)uc);
	act = curthread->deferred_sigact;
	uc->uc_sigmask = curthread->deferred_sigmask;
	memcpy(&info, &curthread->deferred_siginfo, sizeof(siginfo_t));
	/* remove signal */
	curthread->deferred_siginfo.si_signo = 0;
	handle_signal(&act, info.si_signo, &info, uc);
}