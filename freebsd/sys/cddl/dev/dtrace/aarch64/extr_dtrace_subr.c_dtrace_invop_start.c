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
struct trapframe {int tf_elr; size_t tf_sp; size_t* tf_x; int tf_lr; } ;
typedef  size_t register_t ;

/* Variables and functions */
 int ARG1_MASK ; 
 int ARG1_SHIFT ; 
 int ARG2_MASK ; 
 int ARG2_SHIFT ; 
 int B_DATA_MASK ; 
 int B_INSTR ; 
 int B_MASK ; 
 scalar_t__ INSN_SIZE ; 
#define  LDP_64 129 
 int LDP_STP_MASK ; 
 int OFFSET_MASK ; 
 int OFFSET_SHIFT ; 
 int /*<<< orphan*/  OFFSET_SIZE ; 
 int RET_INSTR ; 
#define  STP_64 128 
 int dtrace_invop (int,struct trapframe*,int) ; 

__attribute__((used)) static int
dtrace_invop_start(struct trapframe *frame)
{
	int data, invop, reg, update_sp;
	register_t arg1, arg2;
	register_t *sp;
	int offs;
	int tmp;
	int i;

	invop = dtrace_invop(frame->tf_elr, frame, frame->tf_elr);

	tmp = (invop & LDP_STP_MASK);
	if (tmp == STP_64 || tmp == LDP_64) {
		sp = (register_t *)frame->tf_sp;
		data = invop;
		arg1 = (data >> ARG1_SHIFT) & ARG1_MASK;
		arg2 = (data >> ARG2_SHIFT) & ARG2_MASK;

		offs = (data >> OFFSET_SHIFT) & OFFSET_MASK;

		switch (tmp) {
		case STP_64:
			if (offs >> (OFFSET_SIZE - 1))
				sp -= (~offs & OFFSET_MASK) + 1;
			else
				sp += (offs);
			*(sp + 0) = frame->tf_x[arg1];
			*(sp + 1) = frame->tf_x[arg2];
			break;
		case LDP_64:
			frame->tf_x[arg1] = *(sp + 0);
			frame->tf_x[arg2] = *(sp + 1);
			if (offs >> (OFFSET_SIZE - 1))
				sp -= (~offs & OFFSET_MASK) + 1;
			else
				sp += (offs);
			break;
		default:
			break;
		}

		/* Update the stack pointer and program counter to continue */
		frame->tf_sp = (register_t)sp;
		frame->tf_elr += INSN_SIZE;
		return (0);
	}

	if ((invop & B_MASK) == B_INSTR) {
		data = (invop & B_DATA_MASK);
		/* The data is the number of 4-byte words to change the pc */
		data *= 4;
		frame->tf_elr += data;
		return (0);
	}

	if (invop == RET_INSTR) {
		frame->tf_elr = frame->tf_lr;
		return (0);
	}

	return (-1);
}