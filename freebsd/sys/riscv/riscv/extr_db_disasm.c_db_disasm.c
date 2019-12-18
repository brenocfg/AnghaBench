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
typedef  int /*<<< orphan*/  uint32_t ;
struct riscv_op {scalar_t__ (* match_func ) (struct riscv_op*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_get_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oprint (struct riscv_op*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct riscv_op* riscv_c_opcodes ; 
 struct riscv_op* riscv_opcodes ; 
 scalar_t__ stub1 (struct riscv_op*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct riscv_op*,int /*<<< orphan*/ ) ; 

vm_offset_t
db_disasm(vm_offset_t loc, bool altfmt)
{
	struct riscv_op *op;
	uint32_t insn;
	int j;

	insn = db_get_value(loc, 4, 0);
	for (j = 0; riscv_opcodes[j].name != NULL; j++) {
		op = &riscv_opcodes[j];
		if (op->match_func(op, insn)) {
			oprint(op, loc, insn);
			return(loc + 4);
		}
	};

	insn = db_get_value(loc, 2, 0);
	for (j = 0; riscv_c_opcodes[j].name != NULL; j++) {
		op = &riscv_c_opcodes[j];
		if (op->match_func(op, insn)) {
			oprint(op, loc, insn);
			break;
		}
	};

	return(loc + 2);
}