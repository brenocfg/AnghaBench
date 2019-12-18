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
struct vie {int opsize; size_t reg; int immediate; TYPE_1__ op; } ;
typedef  int /*<<< orphan*/  mem_region_write_t ;
typedef  int (* mem_region_read_t ) (void*,int,int,int*,int,void*) ;
typedef  enum vm_reg_name { ____Placeholder_vm_reg_name } vm_reg_name ;

/* Variables and functions */
 int EINVAL ; 
 int RFLAGS_STATUS_BITS ; 
 int VM_REG_GUEST_RFLAGS ; 
 int getcc (int,int,int) ; 
 int* gpr_map ; 
 int vie_read_register (void*,int,int,int*) ; 
 int vie_update_register (void*,int,int,int,int) ; 

__attribute__((used)) static int
emulate_cmp(void *vm, int vcpuid, uint64_t gpa, struct vie *vie,
	    mem_region_read_t memread, mem_region_write_t memwrite, void *arg)
{
	int error, size;
	uint64_t regop, memop, op1, op2, rflags, rflags2;
	enum vm_reg_name reg;

	size = vie->opsize;
	switch (vie->op.op_byte) {
	case 0x39:
	case 0x3B:
		/*
		 * 39/r		CMP r/m16, r16
		 * 39/r		CMP r/m32, r32
		 * REX.W 39/r	CMP r/m64, r64
		 *
		 * 3B/r		CMP r16, r/m16
		 * 3B/r		CMP r32, r/m32
		 * REX.W + 3B/r	CMP r64, r/m64
		 *
		 * Compare the first operand with the second operand and
		 * set status flags in EFLAGS register. The comparison is
		 * performed by subtracting the second operand from the first
		 * operand and then setting the status flags.
		 */

		/* Get the register operand */
		reg = gpr_map[vie->reg];
		error = vie_read_register(vm, vcpuid, reg, &regop);
		if (error)
			return (error);

		/* Get the memory operand */
		error = memread(vm, vcpuid, gpa, &memop, size, arg);
		if (error)
			return (error);

		if (vie->op.op_byte == 0x3B) {
			op1 = regop;
			op2 = memop;
		} else {
			op1 = memop;
			op2 = regop;
		}
		rflags2 = getcc(size, op1, op2);
		break;
	case 0x80:
	case 0x81:
	case 0x83:
		/*
		 * 80 /7		cmp r/m8, imm8
		 * REX + 80 /7		cmp r/m8, imm8
		 *
		 * 81 /7		cmp r/m16, imm16
		 * 81 /7		cmp r/m32, imm32
		 * REX.W + 81 /7	cmp r/m64, imm32 sign-extended to 64
		 *
		 * 83 /7		cmp r/m16, imm8 sign-extended to 16
		 * 83 /7		cmp r/m32, imm8 sign-extended to 32
		 * REX.W + 83 /7	cmp r/m64, imm8 sign-extended to 64
		 *
		 * Compare mem (ModRM:r/m) with immediate and set
		 * status flags according to the results.  The
		 * comparison is performed by subtracting the
		 * immediate from the first operand and then setting
		 * the status flags.
		 *
		 */
		if (vie->op.op_byte == 0x80)
			size = 1;

		/* get the first operand */
                error = memread(vm, vcpuid, gpa, &op1, size, arg);
		if (error)
			return (error);

		rflags2 = getcc(size, op1, vie->immediate);
		break;
	default:
		return (EINVAL);
	}
	error = vie_read_register(vm, vcpuid, VM_REG_GUEST_RFLAGS, &rflags);
	if (error)
		return (error);
	rflags &= ~RFLAGS_STATUS_BITS;
	rflags |= rflags2 & RFLAGS_STATUS_BITS;

	error = vie_update_register(vm, vcpuid, VM_REG_GUEST_RFLAGS, rflags, 8);
	return (error);
}