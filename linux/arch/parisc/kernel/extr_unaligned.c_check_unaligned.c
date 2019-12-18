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
struct pt_regs {int iir; unsigned long ior; } ;

/* Variables and functions */
 int OPCODE1_MASK ; 
 int OPCODE4_MASK ; 
#define  OPCODE_LDH_I 142 
#define  OPCODE_LDH_L 141 
#define  OPCODE_LDH_S 140 
#define  OPCODE_LDWA_I 139 
#define  OPCODE_LDWA_S 138 
#define  OPCODE_LDWM 137 
#define  OPCODE_LDW_I 136 
#define  OPCODE_LDW_L 135 
#define  OPCODE_LDW_S 134 
#define  OPCODE_STH 133 
#define  OPCODE_STH_L 132 
#define  OPCODE_STW 131 
#define  OPCODE_STWA 130 
#define  OPCODE_STWM 129 
#define  OPCODE_STW_L 128 

int
check_unaligned(struct pt_regs *regs)
{
	unsigned long align_mask;

	/* Get alignment mask */

	align_mask = 0UL;
	switch (regs->iir & OPCODE1_MASK) {

	case OPCODE_LDH_I:
	case OPCODE_LDH_S:
	case OPCODE_STH:
		align_mask = 1UL;
		break;

	case OPCODE_LDW_I:
	case OPCODE_LDWA_I:
	case OPCODE_LDW_S:
	case OPCODE_LDWA_S:
	case OPCODE_STW:
	case OPCODE_STWA:
		align_mask = 3UL;
		break;

	default:
		switch (regs->iir & OPCODE4_MASK) {
		case OPCODE_LDH_L:
		case OPCODE_STH_L:
			align_mask = 1UL;
			break;
		case OPCODE_LDW_L:
		case OPCODE_LDWM:
		case OPCODE_STW_L:
		case OPCODE_STWM:
			align_mask = 3UL;
			break;
		}
		break;
	}

	return (int)(regs->ior & align_mask);
}