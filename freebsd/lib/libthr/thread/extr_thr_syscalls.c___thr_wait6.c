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
struct __wrusage {int dummy; } ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  idtype_t ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 scalar_t__ __sys_wait6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,struct __wrusage*,int /*<<< orphan*/ *) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter (struct pthread*) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int) ; 

__attribute__((used)) static pid_t
__thr_wait6(idtype_t idtype, id_t id, int *status, int options,
    struct __wrusage *ru, siginfo_t *infop)
{
	struct pthread *curthread;
	pid_t ret;

	curthread = _get_curthread();
	_thr_cancel_enter(curthread);
	ret = __sys_wait6(idtype, id, status, options, ru, infop);
	_thr_cancel_leave(curthread, ret <= 0);
	return (ret);
}