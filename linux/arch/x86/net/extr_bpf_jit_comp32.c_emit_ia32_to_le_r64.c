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
typedef  int /*<<< orphan*/  u8 ;
struct bpf_prog_aux {int /*<<< orphan*/  verifier_zext; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT1 (int) ; 
 int /*<<< orphan*/  EMIT2 (int,int) ; 
 int /*<<< orphan*/  EMIT3 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IA32_EAX ; 
 int /*<<< orphan*/  IA32_EBP ; 
 int /*<<< orphan*/  IA32_EDX ; 
 int /*<<< orphan*/  STACK_VAR (int /*<<< orphan*/ ) ; 
 int add_2reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 

__attribute__((used)) static inline void emit_ia32_to_le_r64(const u8 dst[], s32 val,
					 bool dstk, u8 **pprog,
					 const struct bpf_prog_aux *aux)
{
	u8 *prog = *pprog;
	int cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk && val != 64) {
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	}
	switch (val) {
	case 16:
		/*
		 * Emit 'movzwl eax,ax' to zero extend 16-bit
		 * into 64 bit
		 */
		EMIT2(0x0F, 0xB7);
		EMIT1(add_2reg(0xC0, dreg_lo, dreg_lo));
		if (!aux->verifier_zext)
			/* xor dreg_hi,dreg_hi */
			EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
		break;
	case 32:
		if (!aux->verifier_zext)
			/* xor dreg_hi,dreg_hi */
			EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
		break;
	case 64:
		/* nop */
		break;
	}

	if (dstk && val != 64) {
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	}
	*pprog = prog;
}