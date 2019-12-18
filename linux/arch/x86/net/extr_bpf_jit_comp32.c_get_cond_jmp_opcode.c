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
typedef  int u8 ;

/* Variables and functions */
#define  BPF_JEQ 138 
#define  BPF_JGE 137 
#define  BPF_JGT 136 
#define  BPF_JLE 135 
#define  BPF_JLT 134 
#define  BPF_JNE 133 
#define  BPF_JSET 132 
#define  BPF_JSGE 131 
#define  BPF_JSGT 130 
#define  BPF_JSLE 129 
#define  BPF_JSLT 128 
 int COND_JMP_OPCODE_INVALID ; 
 int IA32_JA ; 
 int IA32_JAE ; 
 int IA32_JB ; 
 int IA32_JBE ; 
 int IA32_JE ; 
 int IA32_JG ; 
 int IA32_JGE ; 
 int IA32_JL ; 
 int IA32_JLE ; 
 int IA32_JNE ; 

__attribute__((used)) static u8 get_cond_jmp_opcode(const u8 op, bool is_cmp_lo)
{
	u8 jmp_cond;

	/* Convert BPF opcode to x86 */
	switch (op) {
	case BPF_JEQ:
		jmp_cond = IA32_JE;
		break;
	case BPF_JSET:
	case BPF_JNE:
		jmp_cond = IA32_JNE;
		break;
	case BPF_JGT:
		/* GT is unsigned '>', JA in x86 */
		jmp_cond = IA32_JA;
		break;
	case BPF_JLT:
		/* LT is unsigned '<', JB in x86 */
		jmp_cond = IA32_JB;
		break;
	case BPF_JGE:
		/* GE is unsigned '>=', JAE in x86 */
		jmp_cond = IA32_JAE;
		break;
	case BPF_JLE:
		/* LE is unsigned '<=', JBE in x86 */
		jmp_cond = IA32_JBE;
		break;
	case BPF_JSGT:
		if (!is_cmp_lo)
			/* Signed '>', GT in x86 */
			jmp_cond = IA32_JG;
		else
			/* GT is unsigned '>', JA in x86 */
			jmp_cond = IA32_JA;
		break;
	case BPF_JSLT:
		if (!is_cmp_lo)
			/* Signed '<', LT in x86 */
			jmp_cond = IA32_JL;
		else
			/* LT is unsigned '<', JB in x86 */
			jmp_cond = IA32_JB;
		break;
	case BPF_JSGE:
		if (!is_cmp_lo)
			/* Signed '>=', GE in x86 */
			jmp_cond = IA32_JGE;
		else
			/* GE is unsigned '>=', JAE in x86 */
			jmp_cond = IA32_JAE;
		break;
	case BPF_JSLE:
		if (!is_cmp_lo)
			/* Signed '<=', LE in x86 */
			jmp_cond = IA32_JLE;
		else
			/* LE is unsigned '<=', JBE in x86 */
			jmp_cond = IA32_JBE;
		break;
	default: /* to silence GCC warning */
		jmp_cond = COND_JMP_OPCODE_INVALID;
		break;
	}

	return jmp_cond;
}