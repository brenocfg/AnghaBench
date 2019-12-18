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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ const BPF_MOD ; 
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ const IA32_EAX ; 
 scalar_t__ const IA32_EBP ; 
 scalar_t__ const IA32_ECX ; 
 scalar_t__ const IA32_EDX ; 
 int /*<<< orphan*/  STACK_VAR (scalar_t__ const) ; 
 int /*<<< orphan*/  add_1reg (int,scalar_t__ const) ; 
 int /*<<< orphan*/  add_2reg (int,scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static inline void emit_ia32_div_mod_r(const u8 op, const u8 dst, const u8 src,
				       bool dstk, bool sstk, u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;

	if (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(src));
	else if (src != IA32_ECX)
		/* mov ecx,src */
		EMIT2(0x8B, add_2reg(0xC0, src, IA32_ECX));

	if (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst));
	else
		/* mov eax,dst */
		EMIT2(0x8B, add_2reg(0xC0, dst, IA32_EAX));

	/* xor edx,edx */
	EMIT2(0x31, add_2reg(0xC0, IA32_EDX, IA32_EDX));
	/* div ecx */
	EMIT2(0xF7, add_1reg(0xF0, IA32_ECX));

	if (op == BPF_MOD) {
		if (dstk)
			EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EDX),
			      STACK_VAR(dst));
		else
			EMIT2(0x89, add_2reg(0xC0, dst, IA32_EDX));
	} else {
		if (dstk)
			EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
			      STACK_VAR(dst));
		else
			EMIT2(0x89, add_2reg(0xC0, dst, IA32_EAX));
	}
	*pprog = prog;
}