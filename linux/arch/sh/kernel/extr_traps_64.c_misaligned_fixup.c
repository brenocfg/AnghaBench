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
struct pt_regs {int pc; } ;
typedef  int insn_size_t ;

/* Variables and functions */
 unsigned int UM_FIXUP ; 
 int misaligned_fpu_load (struct pt_regs*,int,int,int,int) ; 
 int misaligned_fpu_store (struct pt_regs*,int,int,int,int) ; 
 int misaligned_load (struct pt_regs*,int,int,int,int) ; 
 int misaligned_store (struct pt_regs*,int,int,int) ; 
 int read_opcode (int,int*,int /*<<< orphan*/ ) ; 
 unsigned int unaligned_user_action () ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static int misaligned_fixup(struct pt_regs *regs)
{
	insn_size_t opcode;
	int error;
	int major, minor;
	unsigned int user_action;

	user_action = unaligned_user_action();
	if (!(user_action & UM_FIXUP))
		return -1;

	error = read_opcode(regs->pc, &opcode, user_mode(regs));
	if (error < 0) {
		return error;
	}
	major = (opcode >> 26) & 0x3f;
	minor = (opcode >> 16) & 0xf;

	switch (major) {
		case (0x84>>2): /* LD.W */
			error = misaligned_load(regs, opcode, 1, 1, 1);
			break;
		case (0xb0>>2): /* LD.UW */
			error = misaligned_load(regs, opcode, 1, 1, 0);
			break;
		case (0x88>>2): /* LD.L */
			error = misaligned_load(regs, opcode, 1, 2, 1);
			break;
		case (0x8c>>2): /* LD.Q */
			error = misaligned_load(regs, opcode, 1, 3, 0);
			break;

		case (0xa4>>2): /* ST.W */
			error = misaligned_store(regs, opcode, 1, 1);
			break;
		case (0xa8>>2): /* ST.L */
			error = misaligned_store(regs, opcode, 1, 2);
			break;
		case (0xac>>2): /* ST.Q */
			error = misaligned_store(regs, opcode, 1, 3);
			break;

		case (0x40>>2): /* indexed loads */
			switch (minor) {
				case 0x1: /* LDX.W */
					error = misaligned_load(regs, opcode, 0, 1, 1);
					break;
				case 0x5: /* LDX.UW */
					error = misaligned_load(regs, opcode, 0, 1, 0);
					break;
				case 0x2: /* LDX.L */
					error = misaligned_load(regs, opcode, 0, 2, 1);
					break;
				case 0x3: /* LDX.Q */
					error = misaligned_load(regs, opcode, 0, 3, 0);
					break;
				default:
					error = -1;
					break;
			}
			break;

		case (0x60>>2): /* indexed stores */
			switch (minor) {
				case 0x1: /* STX.W */
					error = misaligned_store(regs, opcode, 0, 1);
					break;
				case 0x2: /* STX.L */
					error = misaligned_store(regs, opcode, 0, 2);
					break;
				case 0x3: /* STX.Q */
					error = misaligned_store(regs, opcode, 0, 3);
					break;
				default:
					error = -1;
					break;
			}
			break;

		case (0x94>>2): /* FLD.S */
			error = misaligned_fpu_load(regs, opcode, 1, 2, 0);
			break;
		case (0x98>>2): /* FLD.P */
			error = misaligned_fpu_load(regs, opcode, 1, 3, 1);
			break;
		case (0x9c>>2): /* FLD.D */
			error = misaligned_fpu_load(regs, opcode, 1, 3, 0);
			break;
		case (0x1c>>2): /* floating indexed loads */
			switch (minor) {
			case 0x8: /* FLDX.S */
				error = misaligned_fpu_load(regs, opcode, 0, 2, 0);
				break;
			case 0xd: /* FLDX.P */
				error = misaligned_fpu_load(regs, opcode, 0, 3, 1);
				break;
			case 0x9: /* FLDX.D */
				error = misaligned_fpu_load(regs, opcode, 0, 3, 0);
				break;
			default:
				error = -1;
				break;
			}
			break;
		case (0xb4>>2): /* FLD.S */
			error = misaligned_fpu_store(regs, opcode, 1, 2, 0);
			break;
		case (0xb8>>2): /* FLD.P */
			error = misaligned_fpu_store(regs, opcode, 1, 3, 1);
			break;
		case (0xbc>>2): /* FLD.D */
			error = misaligned_fpu_store(regs, opcode, 1, 3, 0);
			break;
		case (0x3c>>2): /* floating indexed stores */
			switch (minor) {
			case 0x8: /* FSTX.S */
				error = misaligned_fpu_store(regs, opcode, 0, 2, 0);
				break;
			case 0xd: /* FSTX.P */
				error = misaligned_fpu_store(regs, opcode, 0, 3, 1);
				break;
			case 0x9: /* FSTX.D */
				error = misaligned_fpu_store(regs, opcode, 0, 3, 0);
				break;
			default:
				error = -1;
				break;
			}
			break;

		default:
			/* Fault */
			error = -1;
			break;
	}

	if (error < 0) {
		return error;
	} else {
		regs->pc += 4; /* Skip the instruction that's just been emulated */
		return 0;
	}
}