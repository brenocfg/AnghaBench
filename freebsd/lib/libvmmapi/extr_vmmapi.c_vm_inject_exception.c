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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_exception {int cpuid; int vector; int error_code_valid; int restart_instruction; int /*<<< orphan*/  error_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_INJECT_EXCEPTION ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_exception*) ; 

int
vm_inject_exception(struct vmctx *ctx, int vcpu, int vector, int errcode_valid,
    uint32_t errcode, int restart_instruction)
{
	struct vm_exception exc;

	exc.cpuid = vcpu;
	exc.vector = vector;
	exc.error_code = errcode;
	exc.error_code_valid = errcode_valid;
	exc.restart_instruction = restart_instruction;

	return (ioctl(ctx->fd, VM_INJECT_EXCEPTION, &exc));
}