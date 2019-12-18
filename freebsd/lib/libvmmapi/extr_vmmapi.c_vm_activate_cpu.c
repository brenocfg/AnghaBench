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
struct vm_activate_cpu {int vcpuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_ACTIVATE_CPU ; 
 int /*<<< orphan*/  bzero (struct vm_activate_cpu*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_activate_cpu*) ; 

int
vm_activate_cpu(struct vmctx *ctx, int vcpu)
{
	struct vm_activate_cpu ac;
	int error;

	bzero(&ac, sizeof(struct vm_activate_cpu));
	ac.vcpuid = vcpu;
	error = ioctl(ctx->fd, VM_ACTIVATE_CPU, &ac);
	return (error);
}