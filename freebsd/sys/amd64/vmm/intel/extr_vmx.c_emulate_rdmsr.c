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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct vmxctx {int dummy; } ;
struct vmx {struct vmxctx* ctx; int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VM_REG_GUEST_RAX ; 
 int /*<<< orphan*/  VM_REG_GUEST_RDX ; 
 scalar_t__ lapic_msr (int /*<<< orphan*/ ) ; 
 int lapic_rdmsr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*) ; 
 int vmx_rdmsr (struct vmx*,int,int /*<<< orphan*/ ,int*,int*) ; 
 int vmxctx_setreg (struct vmxctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
emulate_rdmsr(struct vmx *vmx, int vcpuid, u_int num, bool *retu)
{
	struct vmxctx *vmxctx;
	uint64_t result;
	uint32_t eax, edx;
	int error;

	if (lapic_msr(num))
		error = lapic_rdmsr(vmx->vm, vcpuid, num, &result, retu);
	else
		error = vmx_rdmsr(vmx, vcpuid, num, &result, retu);

	if (error == 0) {
		eax = result;
		vmxctx = &vmx->ctx[vcpuid];
		error = vmxctx_setreg(vmxctx, VM_REG_GUEST_RAX, eax);
		KASSERT(error == 0, ("vmxctx_setreg(rax) error %d", error));

		edx = result >> 32;
		error = vmxctx_setreg(vmxctx, VM_REG_GUEST_RDX, edx);
		KASSERT(error == 0, ("vmxctx_setreg(rdx) error %d", error));
	}

	return (error);
}