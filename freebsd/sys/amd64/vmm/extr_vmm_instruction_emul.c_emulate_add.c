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
struct vie {int opsize; size_t reg; TYPE_1__ op; } ;
typedef  int /*<<< orphan*/  mem_region_write_t ;
typedef  int (* mem_region_read_t ) (void*,int,int,int*,int,void*) ;
typedef  enum vm_reg_name { ____Placeholder_vm_reg_name } vm_reg_name ;

/* Variables and functions */
 int EINVAL ; 
 int RFLAGS_STATUS_BITS ; 
 int VM_REG_GUEST_RFLAGS ; 
 int getaddflags (int,int,int) ; 
 int* gpr_map ; 
 int vie_read_register (void*,int,int,int*) ; 
 int vie_update_register (void*,int,int,int,int) ; 

__attribute__((used)) static int
emulate_add(void *vm, int vcpuid, uint64_t gpa, struct vie *vie,
	    mem_region_read_t memread, mem_region_write_t memwrite, void *arg)
{
	int error, size;
	uint64_t nval, rflags, rflags2, val1, val2;
	enum vm_reg_name reg;

	size = vie->opsize;
	error = EINVAL;

	switch (vie->op.op_byte) {
	case 0x03:
		/*
		 * ADD r/m to r and store the result in r
		 *
		 * 03/r            ADD r16, r/m16
		 * 03/r            ADD r32, r/m32
		 * REX.W + 03/r    ADD r64, r/m64
		 */

		/* get the first operand */
		reg = gpr_map[vie->reg];
		error = vie_read_register(vm, vcpuid, reg, &val1);
		if (error)
			break;

		/* get the second operand */
		error = memread(vm, vcpuid, gpa, &val2, size, arg);
		if (error)
			break;

		/* perform the operation and write the result */
		nval = val1 + val2;
		error = vie_update_register(vm, vcpuid, reg, nval, size);
		break;
	default:
		break;
	}

	if (!error) {
		rflags2 = getaddflags(size, val1, val2);
		error = vie_read_register(vm, vcpuid, VM_REG_GUEST_RFLAGS,
		    &rflags);
		if (error)
			return (error);

		rflags &= ~RFLAGS_STATUS_BITS;
		rflags |= rflags2 & RFLAGS_STATUS_BITS;
		error = vie_update_register(vm, vcpuid, VM_REG_GUEST_RFLAGS,
		    rflags, 8);
	}

	return (error);
}