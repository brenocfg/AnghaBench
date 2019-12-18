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
struct coverage_entry {int regs; TYPE_1__* header; } ;
typedef  int kprobe_opcode_t ;
typedef  enum decode_reg_type { ____Placeholder_decode_reg_type } decode_reg_type ;
struct TYPE_4__ {int bits; } ;
struct TYPE_3__ {TYPE_2__ type_regs; } ;

/* Variables and functions */
 int COVERAGE_ANY_REG ; 
 int COVERAGE_PC ; 
 int COVERAGE_PCWB ; 
 int COVERAGE_SP ; 
 int DECODE_TYPE_BITS ; 
#define  REG_TYPE_ANY 138 
#define  REG_TYPE_NONE 137 
#define  REG_TYPE_NOPC 136 
#define  REG_TYPE_NOPCWB 135 
#define  REG_TYPE_NOPCX 134 
#define  REG_TYPE_NOSP 133 
#define  REG_TYPE_NOSPPC 132 
#define  REG_TYPE_NOSPPCX 131 
#define  REG_TYPE_PC 130 
#define  REG_TYPE_SAMEAS16 129 
#define  REG_TYPE_SP 128 
 int /*<<< orphan*/  is_writeback (int) ; 

__attribute__((used)) static void
coverage_add_registers(struct coverage_entry *entry, kprobe_opcode_t insn)
{
	int regs = entry->header->type_regs.bits >> DECODE_TYPE_BITS;
	int i;
	for (i = 0; i < 20; i += 4) {
		enum decode_reg_type reg_type = (regs >> i) & 0xf;
		int reg = (insn >> i) & 0xf;
		int flag;

		if (!reg_type)
			continue;

		if (reg == 13)
			flag = COVERAGE_SP;
		else if (reg == 15)
			flag = COVERAGE_PC;
		else
			flag = COVERAGE_ANY_REG;
		entry->regs &= ~(flag << i);

		switch (reg_type) {

		case REG_TYPE_NONE:
		case REG_TYPE_ANY:
		case REG_TYPE_SAMEAS16:
			break;

		case REG_TYPE_SP:
			if (reg != 13)
				return;
			break;

		case REG_TYPE_PC:
			if (reg != 15)
				return;
			break;

		case REG_TYPE_NOSP:
			if (reg == 13)
				return;
			break;

		case REG_TYPE_NOSPPC:
		case REG_TYPE_NOSPPCX:
			if (reg == 13 || reg == 15)
				return;
			break;

		case REG_TYPE_NOPCWB:
			if (!is_writeback(insn))
				break;
			if (reg == 15) {
				entry->regs &= ~(COVERAGE_PCWB << i);
				return;
			}
			break;

		case REG_TYPE_NOPC:
		case REG_TYPE_NOPCX:
			if (reg == 15)
				return;
			break;
		}

	}
}