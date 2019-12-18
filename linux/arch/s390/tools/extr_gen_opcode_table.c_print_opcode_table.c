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
struct insn {TYPE_1__* type; int /*<<< orphan*/  opcode; } ;
struct gen_opcode {int nr; struct insn* insn; } ;
struct TYPE_2__ {scalar_t__ byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_group (struct gen_opcode*,struct insn*,int) ; 
 int /*<<< orphan*/  cmpopcode ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_opcode (struct insn*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  qsort (struct insn*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void print_opcode_table(struct gen_opcode *desc)
{
	char opcode[2] = "";
	struct insn *insn;
	int i, offset;

	qsort(desc->insn, desc->nr, sizeof(*desc->insn), cmpopcode);
	printf("#define OPCODE_TABLE_INITIALIZER { \\\n");
	offset = 0;
	for (i = 0; i < desc->nr; i++) {
		insn = &desc->insn[i];
		if (insn->type->byte == 0)
			continue;
		add_to_group(desc, insn, offset);
		if (strncmp(opcode, insn->opcode, 2)) {
			memcpy(opcode, insn->opcode, 2);
			printf("\t/* %.2s */ \\\n", opcode);
		}
		print_opcode(insn, offset);
		offset++;
	}
	printf("\t/* 1-byte opcode instructions */ \\\n");
	for (i = 0; i < desc->nr; i++) {
		insn = &desc->insn[i];
		if (insn->type->byte != 0)
			continue;
		add_to_group(desc, insn, offset);
		print_opcode(insn, offset);
		offset++;
	}
	printf("}\n\n");
}