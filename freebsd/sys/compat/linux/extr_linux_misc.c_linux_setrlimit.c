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
typedef  int u_int ;
struct thread {int dummy; } ;
struct rlimit {void* rlim_max; void* rlim_cur; } ;
struct linux_setrlimit_args {size_t resource; int /*<<< orphan*/  rlim; } ;
struct l_rlimit {scalar_t__ rlim_max; scalar_t__ rlim_cur; } ;
typedef  void* rlim_t ;
typedef  int /*<<< orphan*/  rlim ;

/* Variables and functions */
 int EINVAL ; 
 size_t LINUX_RLIM_NLIMITS ; 
 int copyin (int /*<<< orphan*/ ,struct l_rlimit*,int) ; 
 int kern_setrlimit (struct thread*,int,struct rlimit*) ; 
 int* linux_to_bsd_resource ; 

int
linux_setrlimit(struct thread *td, struct linux_setrlimit_args *args)
{
	struct rlimit bsd_rlim;
	struct l_rlimit rlim;
	u_int which;
	int error;

	if (args->resource >= LINUX_RLIM_NLIMITS)
		return (EINVAL);

	which = linux_to_bsd_resource[args->resource];
	if (which == -1)
		return (EINVAL);

	error = copyin(args->rlim, &rlim, sizeof(rlim));
	if (error)
		return (error);

	bsd_rlim.rlim_cur = (rlim_t)rlim.rlim_cur;
	bsd_rlim.rlim_max = (rlim_t)rlim.rlim_max;
	return (kern_setrlimit(td, which, &bsd_rlim));
}