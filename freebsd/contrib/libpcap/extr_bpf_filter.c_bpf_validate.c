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
typedef  size_t u_int ;
struct bpf_insn {size_t k; size_t jt; size_t jf; int /*<<< orphan*/  code; } ;

/* Variables and functions */
#define  BPF_ABS 157 
#define  BPF_ADD 156 
#define  BPF_ALU 155 
#define  BPF_AND 154 
 int const BPF_CLASS (int /*<<< orphan*/ ) ; 
#define  BPF_DIV 153 
#define  BPF_IMM 152 
#define  BPF_IND 151 
#define  BPF_JA 150 
#define  BPF_JEQ 149 
#define  BPF_JGE 148 
#define  BPF_JGT 147 
#define  BPF_JMP 146 
#define  BPF_JSET 145 
 int /*<<< orphan*/  BPF_K ; 
#define  BPF_LD 144 
#define  BPF_LDX 143 
#define  BPF_LEN 142 
#define  BPF_LSH 141 
#define  BPF_MEM 140 
 size_t BPF_MEMWORDS ; 
#define  BPF_MISC 139 
#define  BPF_MOD 138 
 int /*<<< orphan*/  BPF_MODE (int /*<<< orphan*/ ) ; 
#define  BPF_MSH 137 
#define  BPF_MUL 136 
#define  BPF_NEG 135 
 int /*<<< orphan*/  BPF_OP (int /*<<< orphan*/ ) ; 
#define  BPF_OR 134 
#define  BPF_RET 133 
#define  BPF_RSH 132 
 int /*<<< orphan*/  BPF_SRC (int /*<<< orphan*/ ) ; 
#define  BPF_ST 131 
#define  BPF_STX 130 
#define  BPF_SUB 129 
#define  BPF_XOR 128 

int
bpf_validate(const struct bpf_insn *f, int len)
{
	u_int i, from;
	const struct bpf_insn *p;

	if (len < 1)
		return 0;

	for (i = 0; i < (u_int)len; ++i) {
		p = &f[i];
		switch (BPF_CLASS(p->code)) {
		/*
		 * Check that memory operations use valid addresses.
		 */
		case BPF_LD:
		case BPF_LDX:
			switch (BPF_MODE(p->code)) {
			case BPF_IMM:
				break;
			case BPF_ABS:
			case BPF_IND:
			case BPF_MSH:
				/*
				 * There's no maximum packet data size
				 * in userland.  The runtime packet length
				 * check suffices.
				 */
				break;
			case BPF_MEM:
				if (p->k >= BPF_MEMWORDS)
					return 0;
				break;
			case BPF_LEN:
				break;
			default:
				return 0;
			}
			break;
		case BPF_ST:
		case BPF_STX:
			if (p->k >= BPF_MEMWORDS)
				return 0;
			break;
		case BPF_ALU:
			switch (BPF_OP(p->code)) {
			case BPF_ADD:
			case BPF_SUB:
			case BPF_MUL:
			case BPF_OR:
			case BPF_AND:
			case BPF_XOR:
			case BPF_LSH:
			case BPF_RSH:
			case BPF_NEG:
				break;
			case BPF_DIV:
			case BPF_MOD:
				/*
				 * Check for constant division or modulus
				 * by 0.
				 */
				if (BPF_SRC(p->code) == BPF_K && p->k == 0)
					return 0;
				break;
			default:
				return 0;
			}
			break;
		case BPF_JMP:
			/*
			 * Check that jumps are within the code block,
			 * and that unconditional branches don't go
			 * backwards as a result of an overflow.
			 * Unconditional branches have a 32-bit offset,
			 * so they could overflow; we check to make
			 * sure they don't.  Conditional branches have
			 * an 8-bit offset, and the from address is <=
			 * BPF_MAXINSNS, and we assume that BPF_MAXINSNS
			 * is sufficiently small that adding 255 to it
			 * won't overflow.
			 *
			 * We know that len is <= BPF_MAXINSNS, and we
			 * assume that BPF_MAXINSNS is < the maximum size
			 * of a u_int, so that i + 1 doesn't overflow.
			 *
			 * For userland, we don't know that the from
			 * or len are <= BPF_MAXINSNS, but we know that
			 * from <= len, and, except on a 64-bit system,
			 * it's unlikely that len, if it truly reflects
			 * the size of the program we've been handed,
			 * will be anywhere near the maximum size of
			 * a u_int.  We also don't check for backward
			 * branches, as we currently support them in
			 * userland for the protochain operation.
			 */
			from = i + 1;
			switch (BPF_OP(p->code)) {
			case BPF_JA:
				if (from + p->k >= (u_int)len)
					return 0;
				break;
			case BPF_JEQ:
			case BPF_JGT:
			case BPF_JGE:
			case BPF_JSET:
				if (from + p->jt >= (u_int)len || from + p->jf >= (u_int)len)
					return 0;
				break;
			default:
				return 0;
			}
			break;
		case BPF_RET:
			break;
		case BPF_MISC:
			break;
		default:
			return 0;
		}
	}
	return BPF_CLASS(f[len - 1].code) == BPF_RET;
}