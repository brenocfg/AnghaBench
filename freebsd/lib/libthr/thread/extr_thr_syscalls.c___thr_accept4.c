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
struct sockaddr {int dummy; } ;
struct pthread {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int __sys_accept4 (int,struct sockaddr*,int /*<<< orphan*/ *,int) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter (struct pthread*) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int) ; 

__attribute__((used)) static int
__thr_accept4(int s, struct sockaddr *addr, socklen_t *addrlen, int flags)
{
	struct pthread *curthread;
	int ret;

	curthread = _get_curthread();
	_thr_cancel_enter(curthread);
	ret = __sys_accept4(s, addr, addrlen, flags);
	_thr_cancel_leave(curthread, ret == -1);

 	return (ret);
}