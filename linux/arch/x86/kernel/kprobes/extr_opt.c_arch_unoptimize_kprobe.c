#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  insn; int /*<<< orphan*/  copied_insn; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct optimized_kprobe {TYPE_2__ optinsn; TYPE_1__ kp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAKPOINT_INSTRUCTION ; 
 int RELATIVEJUMP_SIZE ; 
 int /*<<< orphan*/  RELATIVE_ADDR_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_poke_bp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void arch_unoptimize_kprobe(struct optimized_kprobe *op)
{
	u8 insn_buff[RELATIVEJUMP_SIZE];

	/* Set int3 to first byte for kprobes */
	insn_buff[0] = BREAKPOINT_INSTRUCTION;
	memcpy(insn_buff + 1, op->optinsn.copied_insn, RELATIVE_ADDR_SIZE);
	text_poke_bp(op->kp.addr, insn_buff, RELATIVEJUMP_SIZE,
		     op->optinsn.insn);
}