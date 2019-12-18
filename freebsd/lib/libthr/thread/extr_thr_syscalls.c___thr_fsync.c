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

/* Variables and functions */
 int __sys_fsync (int) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter2 (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int) ; 

__attribute__((used)) static int
__thr_fsync(int fd)
{
	struct pthread *curthread;
	int ret;

	curthread = _get_curthread();
	_thr_cancel_enter2(curthread, 0);
	ret = __sys_fsync(fd);
	_thr_cancel_leave(curthread, 1);

	return (ret);
}