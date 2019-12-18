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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct opcode {int mask; int code; int /*<<< orphan*/  name; } ;
typedef  int instr_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_printf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disasm_fields (struct opcode const*,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  op_ill (int,int /*<<< orphan*/ ) ; 

void
dis_ppc(const struct opcode *opcodeset, instr_t instr, vm_offset_t loc)
{
	const struct opcode *op;
	int found = 0;
	int i;
	char disasm_str[80];

	for (i = 0, op = &opcodeset[0];
	    found == 0 && op->mask != 0;
	    i++, op = &opcodeset[i]) {
		if ((instr & op->mask) == op->code) {
			found = 1;
			disasm_fields(op, instr, loc, disasm_str,
				sizeof disasm_str);
			db_printf("%s%s\n", op->name, disasm_str);
			return;
		}
	}
	op_ill(instr, loc);
}