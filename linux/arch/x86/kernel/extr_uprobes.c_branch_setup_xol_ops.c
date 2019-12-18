#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int nbytes; int* bytes; } ;
struct TYPE_5__ {int nbytes; } ;
struct insn {TYPE_4__ immediate; int /*<<< orphan*/  length; TYPE_2__ prefixes; TYPE_1__ opcode; } ;
struct TYPE_7__ {int opc1; int /*<<< orphan*/  offs; int /*<<< orphan*/  ilen; } ;
struct arch_uprobe {int /*<<< orphan*/ * ops; TYPE_3__ branch; } ;

/* Variables and functions */
 int ENOSYS ; 
 int ENOTSUPP ; 
 int OPCODE1 (struct insn*) ; 
 int /*<<< orphan*/  OPCODE2 (struct insn*) ; 
 int /*<<< orphan*/  branch_clear_offset (struct arch_uprobe*,struct insn*) ; 
 int /*<<< orphan*/  branch_xol_ops ; 
 int /*<<< orphan*/  is_cond_jmp_opcode (int) ; 

__attribute__((used)) static int branch_setup_xol_ops(struct arch_uprobe *auprobe, struct insn *insn)
{
	u8 opc1 = OPCODE1(insn);
	int i;

	switch (opc1) {
	case 0xeb:	/* jmp 8 */
	case 0xe9:	/* jmp 32 */
	case 0x90:	/* prefix* + nop; same as jmp with .offs = 0 */
		break;

	case 0xe8:	/* call relative */
		branch_clear_offset(auprobe, insn);
		break;

	case 0x0f:
		if (insn->opcode.nbytes != 2)
			return -ENOSYS;
		/*
		 * If it is a "near" conditional jmp, OPCODE2() - 0x10 matches
		 * OPCODE1() of the "short" jmp which checks the same condition.
		 */
		opc1 = OPCODE2(insn) - 0x10;
		/* fall through */
	default:
		if (!is_cond_jmp_opcode(opc1))
			return -ENOSYS;
	}

	/*
	 * 16-bit overrides such as CALLW (66 e8 nn nn) are not supported.
	 * Intel and AMD behavior differ in 64-bit mode: Intel ignores 66 prefix.
	 * No one uses these insns, reject any branch insns with such prefix.
	 */
	for (i = 0; i < insn->prefixes.nbytes; i++) {
		if (insn->prefixes.bytes[i] == 0x66)
			return -ENOTSUPP;
	}

	auprobe->branch.opc1 = opc1;
	auprobe->branch.ilen = insn->length;
	auprobe->branch.offs = insn->immediate.value;

	auprobe->ops = &branch_xol_ops;
	return 0;
}