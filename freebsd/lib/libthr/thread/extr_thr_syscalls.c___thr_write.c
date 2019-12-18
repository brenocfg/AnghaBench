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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ __sys_write (int,void const*,size_t) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter (struct pthread*) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int) ; 

__attribute__((used)) static ssize_t
__thr_write(int fd, const void *buf, size_t nbytes)
{
	struct pthread *curthread;
	ssize_t	ret;

	curthread = _get_curthread();
	_thr_cancel_enter(curthread);
	ret = __sys_write(fd, buf, nbytes);
	_thr_cancel_leave(curthread, (ret <= 0));
	return (ret);
}