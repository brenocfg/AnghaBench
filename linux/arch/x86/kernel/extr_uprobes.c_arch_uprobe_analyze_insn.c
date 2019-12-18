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
typedef  int /*<<< orphan*/  u8 ;
struct mm_struct {int dummy; } ;
struct insn {int /*<<< orphan*/  length; } ;
struct TYPE_2__ {int /*<<< orphan*/  fixups; int /*<<< orphan*/  ilen; } ;
struct arch_uprobe {int /*<<< orphan*/ * ops; TYPE_1__ defparam; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  MODRM_REG (struct insn*) ; 
 int OPCODE1 (struct insn*) ; 
 int /*<<< orphan*/  UPROBE_FIX_CALL ; 
 int /*<<< orphan*/  UPROBE_FIX_IP ; 
 int /*<<< orphan*/  UPROBE_FIX_SETF ; 
 int branch_setup_xol_ops (struct arch_uprobe*,struct insn*) ; 
 int /*<<< orphan*/  default_xol_ops ; 
 int /*<<< orphan*/  is_64bit_mm (struct mm_struct*) ; 
 int push_setup_xol_ops (struct arch_uprobe*,struct insn*) ; 
 int /*<<< orphan*/  riprel_analyze (struct arch_uprobe*,struct insn*) ; 
 int uprobe_init_insn (struct arch_uprobe*,struct insn*,int /*<<< orphan*/ ) ; 

int arch_uprobe_analyze_insn(struct arch_uprobe *auprobe, struct mm_struct *mm, unsigned long addr)
{
	struct insn insn;
	u8 fix_ip_or_call = UPROBE_FIX_IP;
	int ret;

	ret = uprobe_init_insn(auprobe, &insn, is_64bit_mm(mm));
	if (ret)
		return ret;

	ret = branch_setup_xol_ops(auprobe, &insn);
	if (ret != -ENOSYS)
		return ret;

	ret = push_setup_xol_ops(auprobe, &insn);
	if (ret != -ENOSYS)
		return ret;

	/*
	 * Figure out which fixups default_post_xol_op() will need to perform,
	 * and annotate defparam->fixups accordingly.
	 */
	switch (OPCODE1(&insn)) {
	case 0x9d:		/* popf */
		auprobe->defparam.fixups |= UPROBE_FIX_SETF;
		break;
	case 0xc3:		/* ret or lret -- ip is correct */
	case 0xcb:
	case 0xc2:
	case 0xca:
	case 0xea:		/* jmp absolute -- ip is correct */
		fix_ip_or_call = 0;
		break;
	case 0x9a:		/* call absolute - Fix return addr, not ip */
		fix_ip_or_call = UPROBE_FIX_CALL;
		break;
	case 0xff:
		switch (MODRM_REG(&insn)) {
		case 2: case 3:			/* call or lcall, indirect */
			fix_ip_or_call = UPROBE_FIX_CALL;
			break;
		case 4: case 5:			/* jmp or ljmp, indirect */
			fix_ip_or_call = 0;
			break;
		}
		/* fall through */
	default:
		riprel_analyze(auprobe, &insn);
	}

	auprobe->defparam.ilen = insn.length;
	auprobe->defparam.fixups |= fix_ip_or_call;

	auprobe->ops = &default_xol_ops;
	return 0;
}