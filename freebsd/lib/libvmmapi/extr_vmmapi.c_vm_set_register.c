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
typedef  int /*<<< orphan*/  vmreg ;
typedef  int /*<<< orphan*/  uint64_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_register {int cpuid; int regnum; int /*<<< orphan*/  regval; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_SET_REGISTER ; 
 int /*<<< orphan*/  bzero (struct vm_register*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_register*) ; 

int
vm_set_register(struct vmctx *ctx, int vcpu, int reg, uint64_t val)
{
	int error;
	struct vm_register vmreg;

	bzero(&vmreg, sizeof(vmreg));
	vmreg.cpuid = vcpu;
	vmreg.regnum = reg;
	vmreg.regval = val;

	error = ioctl(ctx->fd, VM_SET_REGISTER, &vmreg);
	return (error);
}