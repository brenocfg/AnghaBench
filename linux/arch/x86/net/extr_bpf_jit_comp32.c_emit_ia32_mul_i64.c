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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT2_off32 (int,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IA32_EAX ; 
 int /*<<< orphan*/  IA32_EBP ; 
 int /*<<< orphan*/  IA32_ECX ; 
 int /*<<< orphan*/  IA32_EDX ; 
 int /*<<< orphan*/  STACK_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_1reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_2reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 

__attribute__((used)) static inline void emit_ia32_mul_i64(const u8 dst[], const u32 val,
				     bool dstk, u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;
	u32 hi;

	hi = val & (1<<31) ? (u32)~0 : 0;
	/* movl eax,imm32 */
	EMIT2_off32(0xC7, add_1reg(0xC0, IA32_EAX), val);
	if (dstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(dst_hi));
	else
		/* mul dst_hi */
		EMIT2(0xF7, add_1reg(0xE0, dst_hi));

	/* mov ecx,eax */
	EMIT2(0x89, add_2reg(0xC0, IA32_ECX, IA32_EAX));

	/* movl eax,imm32 */
	EMIT2_off32(0xC7, add_1reg(0xC0, IA32_EAX), hi);
	if (dstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(dst_lo));
	else
		/* mul dst_lo */
		EMIT2(0xF7, add_1reg(0xE0, dst_lo));
	/* add ecx,eax */
	EMIT2(0x01, add_2reg(0xC0, IA32_ECX, IA32_EAX));

	/* movl eax,imm32 */
	EMIT2_off32(0xC7, add_1reg(0xC0, IA32_EAX), val);
	if (dstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(dst_lo));
	else
		/* mul dst_lo */
		EMIT2(0xF7, add_1reg(0xE0, dst_lo));

	/* add ecx,edx */
	EMIT2(0x01, add_2reg(0xC0, IA32_ECX, IA32_EDX));

	if (dstk) {
		/* mov dword ptr [ebp+off],eax */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],ecx */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(dst_hi));
	} else {
		/* mov dword ptr [ebp+off],eax */
		EMIT2(0x89, add_2reg(0xC0, dst_lo, IA32_EAX));
		/* mov dword ptr [ebp+off],ecx */
		EMIT2(0x89, add_2reg(0xC0, dst_hi, IA32_ECX));
	}

	*pprog = prog;
}