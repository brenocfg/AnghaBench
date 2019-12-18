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

/* Variables and functions */
 int /*<<< orphan*/  EMIT2 (int,int) ; 
 int /*<<< orphan*/  EMIT3 (int,int,int) ; 
 int /*<<< orphan*/  IA32_EAX ; 
 int /*<<< orphan*/  IA32_EBP ; 
 int /*<<< orphan*/  IA32_ECX ; 
 int /*<<< orphan*/  IA32_EDX ; 
 int IA32_JB ; 
 int STACK_VAR (int /*<<< orphan*/ ) ; 
 int add_1reg (int,int /*<<< orphan*/ ) ; 
 int add_2reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 
 int /*<<< orphan*/  src_lo ; 

__attribute__((used)) static inline void emit_ia32_lsh_r64(const u8 dst[], const u8 src[],
				     bool dstk, bool sstk, u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	if (dstk) {
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	}

	if (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(src_lo));
	else
		/* mov ecx,src_lo */
		EMIT2(0x8B, add_2reg(0xC0, src_lo, IA32_ECX));

	/* shld dreg_hi,dreg_lo,cl */
	EMIT3(0x0F, 0xA5, add_2reg(0xC0, dreg_hi, dreg_lo));
	/* shl dreg_lo,cl */
	EMIT2(0xD3, add_1reg(0xE0, dreg_lo));

	/* if ecx >= 32, mov dreg_lo into dreg_hi and clear dreg_lo */

	/* cmp ecx,32 */
	EMIT3(0x83, add_1reg(0xF8, IA32_ECX), 32);
	/* skip the next two instructions (4 bytes) when < 32 */
	EMIT2(IA32_JB, 4);

	/* mov dreg_hi,dreg_lo */
	EMIT2(0x89, add_2reg(0xC0, dreg_hi, dreg_lo));
	/* xor dreg_lo,dreg_lo */
	EMIT2(0x33, add_2reg(0xC0, dreg_lo, dreg_lo));

	if (dstk) {
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	}
	/* out: */
	*pprog = prog;
}