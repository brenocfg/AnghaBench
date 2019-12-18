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
struct thread {int dummy; } ;
struct linux_wait4_args {int options; int /*<<< orphan*/ * rusage; int /*<<< orphan*/  status; int /*<<< orphan*/  pid; } ;
struct __wrusage {int /*<<< orphan*/  wru_self; } ;

/* Variables and functions */
 int EINVAL ; 
 int LINUX_WCONTINUED ; 
 int LINUX_WNOHANG ; 
 int LINUX_WUNTRACED ; 
 int WEXITED ; 
 int __WALL ; 
 int __WCLONE ; 
 int __WNOTHREAD ; 
 int linux_common_wait (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct __wrusage*) ; 
 int linux_copyout_rusage (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_to_bsd_waitopts (int,int*) ; 

int
linux_wait4(struct thread *td, struct linux_wait4_args *args)
{
	int error, options;
	struct __wrusage wru, *wrup;

	if (args->options & ~(LINUX_WUNTRACED | LINUX_WNOHANG |
	    LINUX_WCONTINUED | __WCLONE | __WNOTHREAD | __WALL))
		return (EINVAL);

	options = WEXITED;
	linux_to_bsd_waitopts(args->options, &options);

	if (args->rusage != NULL)
		wrup = &wru;
	else
		wrup = NULL;
	error = linux_common_wait(td, args->pid, args->status, options, wrup);
	if (error != 0)
		return (error);
	if (args->rusage != NULL)
		error = linux_copyout_rusage(&wru.wru_self, args->rusage);
	return (error);
}