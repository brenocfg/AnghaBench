#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  nbytes; } ;
struct insn {TYPE_1__ immediate; } ;
struct arch_uprobe {scalar_t__ insn; } ;

/* Variables and functions */
 scalar_t__ insn_offset_immediate (struct insn*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void branch_clear_offset(struct arch_uprobe *auprobe, struct insn *insn)
{
	/*
	 * Turn this insn into "call 1f; 1:", this is what we will execute
	 * out-of-line if ->emulate() fails. We only need this to generate
	 * a trap, so that the probed task receives the correct signal with
	 * the properly filled siginfo.
	 *
	 * But see the comment in ->post_xol(), in the unlikely case it can
	 * succeed. So we need to ensure that the new ->ip can not fall into
	 * the non-canonical area and trigger #GP.
	 *
	 * We could turn it into (say) "pushf", but then we would need to
	 * divorce ->insn[] and ->ixol[]. We need to preserve the 1st byte
	 * of ->insn[] for set_orig_insn().
	 */
	memset(auprobe->insn + insn_offset_immediate(insn),
		0, insn->immediate.nbytes);
}