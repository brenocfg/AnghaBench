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
struct msghdr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int __sys_recvmsg (int,struct msghdr*,int) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter (struct pthread*) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int) ; 

__attribute__((used)) static ssize_t
__thr_recvmsg(int s, struct msghdr *m, int f)
{
	struct pthread *curthread;
	ssize_t ret;

	curthread = _get_curthread();
	_thr_cancel_enter(curthread);
	ret = __sys_recvmsg(s, m, f);
	_thr_cancel_leave(curthread, ret == -1);
	return (ret);
}