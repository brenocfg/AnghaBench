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
 int /*<<< orphan*/  EMIT3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const IA32_EAX ; 
 int /*<<< orphan*/  const IA32_EBP ; 
 int /*<<< orphan*/  const IA32_ECX ; 
 int /*<<< orphan*/  STACK_VAR (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  add_1reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_2reg (int,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void emit_ia32_mul_r(const u8 dst, const u8 src, bool dstk,
				   bool sstk, u8 **pprog)
{
	u8 *prog = *pprog;
	int cnt = 0;
	u8 sreg = sstk ? IA32_ECX : src;

	if (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX), STACK_VAR(src));

	if (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(dst));
	else
		/* mov eax,dst */
		EMIT2(0x8B, add_2reg(0xC0, dst, IA32_EAX));


	EMIT2(0xF7, add_1reg(0xE0, sreg));

	if (dstk)
		/* mov dword ptr [ebp+off],eax */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst));
	else
		/* mov dst,eax */
		EMIT2(0x89, add_2reg(0xC0, dst, IA32_EAX));

	*pprog = prog;
}