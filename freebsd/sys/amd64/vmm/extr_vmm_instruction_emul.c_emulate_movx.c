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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int op_byte; } ;
struct vie {int opsize; size_t reg; TYPE_1__ op; } ;
typedef  int /*<<< orphan*/  mem_region_write_t ;
typedef  int (* mem_region_read_t ) (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*) ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  enum vm_reg_name { ____Placeholder_vm_reg_name } vm_reg_name ;

/* Variables and functions */
 int EINVAL ; 
 int* gpr_map ; 
 int vie_update_register (void*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
emulate_movx(void *vm, int vcpuid, uint64_t gpa, struct vie *vie,
	     mem_region_read_t memread, mem_region_write_t memwrite,
	     void *arg)
{
	int error, size;
	enum vm_reg_name reg;
	uint64_t val;

	size = vie->opsize;
	error = EINVAL;

	switch (vie->op.op_byte) {
	case 0xB6:
		/*
		 * MOV and zero extend byte from mem (ModRM:r/m) to
		 * reg (ModRM:reg).
		 *
		 * 0F B6/r		movzx r16, r/m8
		 * 0F B6/r		movzx r32, r/m8
		 * REX.W + 0F B6/r	movzx r64, r/m8
		 */

		/* get the first operand */
		error = memread(vm, vcpuid, gpa, &val, 1, arg);
		if (error)
			break;

		/* get the second operand */
		reg = gpr_map[vie->reg];

		/* zero-extend byte */
		val = (uint8_t)val;

		/* write the result */
		error = vie_update_register(vm, vcpuid, reg, val, size);
		break;
	case 0xB7:
		/*
		 * MOV and zero extend word from mem (ModRM:r/m) to
		 * reg (ModRM:reg).
		 *
		 * 0F B7/r		movzx r32, r/m16
		 * REX.W + 0F B7/r	movzx r64, r/m16
		 */
		error = memread(vm, vcpuid, gpa, &val, 2, arg);
		if (error)
			return (error);

		reg = gpr_map[vie->reg];

		/* zero-extend word */
		val = (uint16_t)val;

		error = vie_update_register(vm, vcpuid, reg, val, size);
		break;
	case 0xBE:
		/*
		 * MOV and sign extend byte from mem (ModRM:r/m) to
		 * reg (ModRM:reg).
		 *
		 * 0F BE/r		movsx r16, r/m8
		 * 0F BE/r		movsx r32, r/m8
		 * REX.W + 0F BE/r	movsx r64, r/m8
		 */

		/* get the first operand */
		error = memread(vm, vcpuid, gpa, &val, 1, arg);
		if (error)
			break;

		/* get the second operand */
		reg = gpr_map[vie->reg];

		/* sign extend byte */
		val = (int8_t)val;

		/* write the result */
		error = vie_update_register(vm, vcpuid, reg, val, size);
		break;
	default:
		break;
	}
	return (error);
}