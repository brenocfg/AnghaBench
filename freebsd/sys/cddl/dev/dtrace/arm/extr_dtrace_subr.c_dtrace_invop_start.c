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
struct trapframe {int tf_pc; void* tf_r0; void* tf_svc_sp; void* tf_svc_lr; } ;
typedef  void* register_t ;

/* Variables and functions */
 int BIT_LR ; 
 int BIT_PC ; 
 int BIT_SP ; 
#define  DTRACE_INVOP_B 130 
 int DTRACE_INVOP_DATA (int) ; 
 int DTRACE_INVOP_MASK ; 
#define  DTRACE_INVOP_POPM 129 
#define  DTRACE_INVOP_PUSHM 128 
 int dtrace_invop (int,struct trapframe*,int) ; 

__attribute__((used)) static int
dtrace_invop_start(struct trapframe *frame)
{
	register_t *r0, *sp;
	int data, invop, reg, update_sp;

	invop = dtrace_invop(frame->tf_pc, frame, frame->tf_pc);
	switch (invop & DTRACE_INVOP_MASK) {
	case DTRACE_INVOP_PUSHM:
		sp = (register_t *)frame->tf_svc_sp;
		r0 = &frame->tf_r0;
		data = DTRACE_INVOP_DATA(invop);

		/*
		 * Store the pc, lr, and sp. These have their own
		 * entries in the struct.
		 */
		if (data & (1 << BIT_PC)) {
			sp--;
			*sp = frame->tf_pc;
		}
		if (data & (1 << BIT_LR)) {
			sp--;
			*sp = frame->tf_svc_lr;
		}
		if (data & (1 << BIT_SP)) {
			sp--;
			*sp = frame->tf_svc_sp;
		}

		/* Store the general registers */
		for (reg = 12; reg >= 0; reg--) {
			if (data & (1 << reg)) {
				sp--;
				*sp = r0[reg];
			}
		}

		/* Update the stack pointer and program counter to continue */
		frame->tf_svc_sp = (register_t)sp;
		frame->tf_pc += 4;
		break;
	case DTRACE_INVOP_POPM:
		sp = (register_t *)frame->tf_svc_sp;
		r0 = &frame->tf_r0;
		data = DTRACE_INVOP_DATA(invop);

		/* Read the general registers */
		for (reg = 0; reg <= 12; reg++) {
			if (data & (1 << reg)) {
				r0[reg] = *sp;
				sp++;
			}
		}

		/*
		 * Set the stack pointer. If we don't update it here we will
		 * need to update it at the end as the instruction would do
		 */
		update_sp = 1;
		if (data & (1 << BIT_SP)) {
			frame->tf_svc_sp = *sp;
			*sp++;
			update_sp = 0;
		}

		/* Update the link register, we need to use the correct copy */
		if (data & (1 << BIT_LR)) {
			frame->tf_svc_lr = *sp;
			*sp++;
		}
		/*
		 * And the program counter. If it's not in the list skip over
		 * it when we return so to not hit this again.
		 */
		if (data & (1 << BIT_PC)) {
			frame->tf_pc = *sp;
			*sp++;
		} else
			frame->tf_pc += 4;

		/* Update the stack pointer if we haven't already done so */
		if (update_sp)
			frame->tf_svc_sp = (register_t)sp;
		break;
	case DTRACE_INVOP_B:
		data = DTRACE_INVOP_DATA(invop) & 0x00ffffff;
		/* Sign extend the data */
		if ((data & (1 << 23)) != 0)
			data |= 0xff000000;
		/* The data is the number of 4-byte words to change the pc */
		data *= 4;
		data += 8;
		frame->tf_pc += data;
		break;
	default:
		return (-1);
		break;
	}

	return (0);
}