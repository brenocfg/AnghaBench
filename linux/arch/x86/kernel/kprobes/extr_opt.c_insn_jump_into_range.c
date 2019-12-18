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
struct TYPE_3__ {unsigned long value; } ;
struct TYPE_4__ {int* bytes; } ;
struct insn {TYPE_1__ immediate; scalar_t__ next_byte; TYPE_2__ opcode; } ;

/* Variables and functions */

__attribute__((used)) static int insn_jump_into_range(struct insn *insn, unsigned long start, int len)
{
	unsigned long target = 0;

	switch (insn->opcode.bytes[0]) {
	case 0xe0:	/* loopne */
	case 0xe1:	/* loope */
	case 0xe2:	/* loop */
	case 0xe3:	/* jcxz */
	case 0xe9:	/* near relative jump */
	case 0xeb:	/* short relative jump */
		break;
	case 0x0f:
		if ((insn->opcode.bytes[1] & 0xf0) == 0x80) /* jcc near */
			break;
		return 0;
	default:
		if ((insn->opcode.bytes[0] & 0xf0) == 0x70) /* jcc short */
			break;
		return 0;
	}
	target = (unsigned long)insn->next_byte + insn->immediate.value;

	return (start <= target && target <= start + len);
}