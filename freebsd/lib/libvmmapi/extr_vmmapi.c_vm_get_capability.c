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
typedef  int /*<<< orphan*/  vmcap ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_capability {int cpuid; int captype; int capval; } ;
typedef  enum vm_cap_type { ____Placeholder_vm_cap_type } vm_cap_type ;

/* Variables and functions */
 int /*<<< orphan*/  VM_GET_CAPABILITY ; 
 int /*<<< orphan*/  bzero (struct vm_capability*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_capability*) ; 

int
vm_get_capability(struct vmctx *ctx, int vcpu, enum vm_cap_type cap,
		  int *retval)
{
	int error;
	struct vm_capability vmcap;

	bzero(&vmcap, sizeof(vmcap));
	vmcap.cpuid = vcpu;
	vmcap.captype = cap;

	error = ioctl(ctx->fd, VM_GET_CAPABILITY, &vmcap);
	*retval = vmcap.capval;
	return (error);
}