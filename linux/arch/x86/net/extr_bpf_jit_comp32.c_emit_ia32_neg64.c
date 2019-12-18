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
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IA32_EAX ; 
 int /*<<< orphan*/  IA32_EBP ; 
 int /*<<< orphan*/  IA32_EDX ; 
 int STACK_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_1reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_2reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 

__attribute__((used)) static inline void emit_ia32_neg64(const u8 dst[], bool dstk, u8 **pprog)
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

	/* neg dreg_lo */
	EMIT2(0xF7, add_1reg(0xD8, dreg_lo));
	/* adc dreg_hi,0x0 */
	EMIT3(0x83, add_1reg(0xD0, dreg_hi), 0x00);
	/* neg dreg_hi */
	EMIT2(0xF7, add_1reg(0xD8, dreg_hi));

	if (dstk) {
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	}
	*pprog = prog;
}