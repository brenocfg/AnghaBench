#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int op_byte; } ;
struct vie {int opsize; int reg; int /*<<< orphan*/  immediate; TYPE_1__ op; } ;
typedef  int /*<<< orphan*/  mem_region_write_t ;
typedef  int (* mem_region_read_t ) (void*,int,int,int*,int,void*) ;

/* Variables and functions */
 int EINVAL ; 
 int PSL_N ; 
 int PSL_PF ; 
 int PSL_Z ; 
 int RFLAGS_STATUS_BITS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RFLAGS ; 
 int getandflags (int,int,int /*<<< orphan*/ ) ; 
 int vie_read_register (void*,int,int /*<<< orphan*/ ,int*) ; 
 int vie_update_register (void*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
emulate_test(void *vm, int vcpuid, uint64_t gpa, struct vie *vie,
    mem_region_read_t memread, mem_region_write_t memwrite, void *arg)
{
	int error, size;
	uint64_t op1, rflags, rflags2;

	size = vie->opsize;
	error = EINVAL;

	switch (vie->op.op_byte) {
	case 0xF7:
		/*
		 * F7 /0		test r/m16, imm16
		 * F7 /0		test r/m32, imm32
		 * REX.W + F7 /0	test r/m64, imm32 sign-extended to 64
		 *
		 * Test mem (ModRM:r/m) with immediate and set status
		 * flags according to the results.  The comparison is
		 * performed by anding the immediate from the first
		 * operand and then setting the status flags.
		 */
		if ((vie->reg & 7) != 0)
			return (EINVAL);

		error = memread(vm, vcpuid, gpa, &op1, size, arg);
		if (error)
			return (error);

		rflags2 = getandflags(size, op1, vie->immediate);
		break;
	default:
		return (EINVAL);
	}
	error = vie_read_register(vm, vcpuid, VM_REG_GUEST_RFLAGS, &rflags);
	if (error)
		return (error);

	/*
	 * OF and CF are cleared; the SF, ZF and PF flags are set according
	 * to the result; AF is undefined.
	 */
	rflags &= ~RFLAGS_STATUS_BITS;
	rflags |= rflags2 & (PSL_PF | PSL_Z | PSL_N);

	error = vie_update_register(vm, vcpuid, VM_REG_GUEST_RFLAGS, rflags, 8);
	return (error);
}