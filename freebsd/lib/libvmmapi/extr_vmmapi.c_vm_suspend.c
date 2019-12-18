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
typedef  int /*<<< orphan*/  vmsuspend ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_suspend {int how; } ;
typedef  enum vm_suspend_how { ____Placeholder_vm_suspend_how } vm_suspend_how ;

/* Variables and functions */
 int /*<<< orphan*/  VM_SUSPEND ; 
 int /*<<< orphan*/  bzero (struct vm_suspend*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_suspend*) ; 

int
vm_suspend(struct vmctx *ctx, enum vm_suspend_how how)
{
	struct vm_suspend vmsuspend;

	bzero(&vmsuspend, sizeof(vmsuspend));
	vmsuspend.how = how;
	return (ioctl(ctx->fd, VM_SUSPEND, &vmsuspend));
}