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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct trapframe {int /*<<< orphan*/  tf_ra; int /*<<< orphan*/  tf_sepc; scalar_t__ tf_sp; } ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int IMM_MASK ; 
 scalar_t__ INSN_C_SIZE ; 
 scalar_t__ INSN_SIZE ; 
 int MASK_C_JR ; 
 int MASK_C_SDSP ; 
 int MASK_JALR ; 
 int MASK_SD ; 
 int MATCH_C_JR ; 
 int MATCH_C_SDSP ; 
 int MATCH_JALR ; 
 int MATCH_SD ; 
 int RD_MASK ; 
 int RD_SHIFT ; 
 int RS1_MASK ; 
 int RS1_SHIFT ; 
 int RS1_SP ; 
 int RS2_C_MASK ; 
 int RS2_C_RA ; 
 int RS2_MASK ; 
 int RS2_RA ; 
 int X_RA ; 
 int dtrace_invop (int /*<<< orphan*/ ,struct trapframe*,int /*<<< orphan*/ ) ; 
 scalar_t__ match_opcode (int,int,int) ; 

__attribute__((used)) static int
dtrace_invop_start(struct trapframe *frame)
{
	register_t *sp;
	uint32_t uimm;
	uint32_t imm;
	int invop;

	invop = dtrace_invop(frame->tf_sepc, frame, frame->tf_sepc);

	if (match_opcode(invop, (MATCH_SD | RS2_RA | RS1_SP),
	    (MASK_SD | RS2_MASK | RS1_MASK))) {
		/* Non-compressed store of ra to sp */
		imm = (invop >> 7) & 0x1f;
		imm |= ((invop >> 25) & 0x7f) << 5;
		sp = (register_t *)((uint8_t *)frame->tf_sp + imm);
		*sp = frame->tf_ra;
		frame->tf_sepc += INSN_SIZE;
		return (0);
	}

	if (match_opcode(invop, (MATCH_JALR | (X_RA << RS1_SHIFT)),
	    (MASK_JALR | RD_MASK | RS1_MASK | IMM_MASK))) {
		/* Non-compressed ret */
		frame->tf_sepc = frame->tf_ra;
		return (0);
	}

	if (match_opcode(invop, (MATCH_C_SDSP | RS2_C_RA),
	    (MASK_C_SDSP | RS2_C_MASK))) {
		/* 'C'-compressed store of ra to sp */
		uimm = ((invop >> 10) & 0x7) << 3;
		uimm |= ((invop >> 7) & 0x7) << 6;
		sp = (register_t *)((uint8_t *)frame->tf_sp + uimm);
		*sp = frame->tf_ra;
		frame->tf_sepc += INSN_C_SIZE;
		return (0);
	}

	if (match_opcode(invop, (MATCH_C_JR | (X_RA << RD_SHIFT)),
	    (MASK_C_JR | RD_MASK))) {
		/* 'C'-compressed ret */
		frame->tf_sepc = frame->tf_ra;
		return (0);
	}

	return (-1);
}