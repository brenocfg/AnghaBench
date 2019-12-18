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
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_cpuset {int which; int cpusetsize; int /*<<< orphan*/ * cpus; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_GET_CPUS ; 
 int /*<<< orphan*/  bzero (struct vm_cpuset*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_cpuset*) ; 

__attribute__((used)) static int
vm_get_cpus(struct vmctx *ctx, int which, cpuset_t *cpus)
{
	struct vm_cpuset vm_cpuset;
	int error;

	bzero(&vm_cpuset, sizeof(struct vm_cpuset));
	vm_cpuset.which = which;
	vm_cpuset.cpusetsize = sizeof(cpuset_t);
	vm_cpuset.cpus = cpus;

	error = ioctl(ctx->fd, VM_GET_CPUS, &vm_cpuset);
	return (error);
}