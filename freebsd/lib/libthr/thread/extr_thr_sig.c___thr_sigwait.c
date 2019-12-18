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
struct pthread {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int EINTR ; 
 int __sys_sigwait (int /*<<< orphan*/ ,int*) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter (struct pthread*) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int) ; 
 int /*<<< orphan*/  thr_remove_thr_signals (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
__thr_sigwait(const sigset_t *set, int *sig)
{
	struct pthread	*curthread = _get_curthread();
	sigset_t newset;
	int ret;

	do {
		_thr_cancel_enter(curthread);
		ret = __sys_sigwait(thr_remove_thr_signals(set, &newset), sig);
		_thr_cancel_leave(curthread, (ret != 0));
	} while (ret == EINTR);
	return (ret);
}