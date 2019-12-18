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
struct timespec {int dummy; } ;
struct pthread {int dummy; } ;
struct pollfd {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  nfds_t ;

/* Variables and functions */
 int __sys_ppoll (struct pollfd*,int /*<<< orphan*/ ,struct timespec const*,int /*<<< orphan*/  const*) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter (struct pthread*) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int) ; 

__attribute__((used)) static int
__thr_ppoll(struct pollfd pfd[], nfds_t nfds, const struct timespec *
    timeout, const sigset_t *newsigmask)
{
	struct pthread *curthread;
	int ret;

	curthread = _get_curthread();
	_thr_cancel_enter(curthread);
	ret = __sys_ppoll(pfd, nfds, timeout, newsigmask);
	_thr_cancel_leave(curthread, ret == -1);

	return (ret);
}