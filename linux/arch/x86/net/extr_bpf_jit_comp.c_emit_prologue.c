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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EMIT1 (int) ; 
 int /*<<< orphan*/  EMIT2 (int,int) ; 
 int /*<<< orphan*/  EMIT3 (int,int,int) ; 
 int /*<<< orphan*/  EMIT3_off32 (int,int,int,int /*<<< orphan*/ ) ; 
 int PROLOGUE_SIZE ; 
 int /*<<< orphan*/  round_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void emit_prologue(u8 **pprog, u32 stack_depth, bool ebpf_from_cbpf)
{
	u8 *prog = *pprog;
	int cnt = 0;

	EMIT1(0x55);             /* push rbp */
	EMIT3(0x48, 0x89, 0xE5); /* mov rbp, rsp */
	/* sub rsp, rounded_stack_depth */
	EMIT3_off32(0x48, 0x81, 0xEC, round_up(stack_depth, 8));
	EMIT1(0x53);             /* push rbx */
	EMIT2(0x41, 0x55);       /* push r13 */
	EMIT2(0x41, 0x56);       /* push r14 */
	EMIT2(0x41, 0x57);       /* push r15 */
	if (!ebpf_from_cbpf) {
		/* zero init tail_call_cnt */
		EMIT2(0x6a, 0x00);
		BUILD_BUG_ON(cnt != PROLOGUE_SIZE);
	}
	*pprog = prog;
}