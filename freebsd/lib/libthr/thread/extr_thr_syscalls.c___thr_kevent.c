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
struct kevent {int dummy; } ;

/* Variables and functions */
 int __sys_kevent (int,struct kevent const*,int,struct kevent*,int,struct timespec const*) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter (struct pthread*) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int) ; 

__attribute__((used)) static int
__thr_kevent(int kq, const struct kevent *changelist, int nchanges,
    struct kevent *eventlist, int nevents, const struct timespec *timeout)
{
	struct pthread *curthread;
	int ret;

	if (nevents == 0) {
		/*
		 * No blocking, do not make the call cancellable.
		 */
		return (__sys_kevent(kq, changelist, nchanges, eventlist,
		    nevents, timeout));
	}
	curthread = _get_curthread();
	_thr_cancel_enter(curthread);
	ret = __sys_kevent(kq, changelist, nchanges, eventlist, nevents,
	    timeout);
	_thr_cancel_leave(curthread, ret == -1 && nchanges == 0);

	return (ret);
}