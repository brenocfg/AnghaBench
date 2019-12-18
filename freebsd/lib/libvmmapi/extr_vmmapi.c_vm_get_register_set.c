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
typedef  int /*<<< orphan*/  vmregset ;
typedef  int /*<<< orphan*/  uint64_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_register_set {int cpuid; unsigned int count; int const* regnums; int /*<<< orphan*/ * regvals; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_GET_REGISTER_SET ; 
 int /*<<< orphan*/  bzero (struct vm_register_set*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_register_set*) ; 

int
vm_get_register_set(struct vmctx *ctx, int vcpu, unsigned int count,
    const int *regnums, uint64_t *regvals)
{
	int error;
	struct vm_register_set vmregset;

	bzero(&vmregset, sizeof(vmregset));
	vmregset.cpuid = vcpu;
	vmregset.count = count;
	vmregset.regnums = regnums;
	vmregset.regvals = regvals;

	error = ioctl(ctx->fd, VM_GET_REGISTER_SET, &vmregset);
	return (error);
}