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
struct insn {int attr; int opnd_bytes; int addr_bytes; int length; int x86_64; int kaddr; int /*<<< orphan*/  immediate2; int /*<<< orphan*/  immediate1; int /*<<< orphan*/  displacement; int /*<<< orphan*/  sib; int /*<<< orphan*/  modrm; int /*<<< orphan*/  opcode; int /*<<< orphan*/  vex_prefix; int /*<<< orphan*/  rex_prefix; int /*<<< orphan*/  prefixes; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dump_field (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void dump_insn(FILE *fp, struct insn *insn)
{
	fprintf(fp, "Instruction = {\n");
	dump_field(fp, "prefixes", "\t",	&insn->prefixes);
	dump_field(fp, "rex_prefix", "\t",	&insn->rex_prefix);
	dump_field(fp, "vex_prefix", "\t",	&insn->vex_prefix);
	dump_field(fp, "opcode", "\t",		&insn->opcode);
	dump_field(fp, "modrm", "\t",		&insn->modrm);
	dump_field(fp, "sib", "\t",		&insn->sib);
	dump_field(fp, "displacement", "\t",	&insn->displacement);
	dump_field(fp, "immediate1", "\t",	&insn->immediate1);
	dump_field(fp, "immediate2", "\t",	&insn->immediate2);
	fprintf(fp, "\t.attr = %x, .opnd_bytes = %d, .addr_bytes = %d,\n",
		insn->attr, insn->opnd_bytes, insn->addr_bytes);
	fprintf(fp, "\t.length = %d, .x86_64 = %d, .kaddr = %p}\n",
		insn->length, insn->x86_64, insn->kaddr);
}