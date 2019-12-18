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
typedef  int /*<<< orphan*/  vmrun ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_run {int cpuid; int /*<<< orphan*/  vm_exit; } ;
struct vm_exit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_RUN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct vm_exit*,int) ; 
 int /*<<< orphan*/  bzero (struct vm_run*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_run*) ; 

int
vm_run(struct vmctx *ctx, int vcpu, struct vm_exit *vmexit)
{
	int error;
	struct vm_run vmrun;

	bzero(&vmrun, sizeof(vmrun));
	vmrun.cpuid = vcpu;

	error = ioctl(ctx->fd, VM_RUN, &vmrun);
	bcopy(&vmrun.vm_exit, vmexit, sizeof(struct vm_exit));
	return (error);
}