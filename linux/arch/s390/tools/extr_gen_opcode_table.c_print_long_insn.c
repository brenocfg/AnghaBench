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
struct insn {int name_len; char* upper; char* name; } ;
struct gen_opcode {int nr; struct insn* insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_long_insn ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  qsort (struct insn*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_long_insn(struct gen_opcode *desc)
{
	struct insn *insn;
	int i, count;

	qsort(desc->insn, desc->nr, sizeof(*desc->insn), cmp_long_insn);
	count = 0;
	printf("enum {\n");
	for (i = 0; i < desc->nr; i++) {
		insn = &desc->insn[i];
		if (insn->name_len < 6)
			continue;
		printf("\tLONG_INSN_%s,\n", insn->upper);
		count++;
	}
	printf("}; /* %d */\n\n", count);

	printf("#define LONG_INSN_INITIALIZER { \\\n");
	for (i = 0; i < desc->nr; i++) {
		insn = &desc->insn[i];
		if (insn->name_len < 6)
			continue;
		printf("\t[LONG_INSN_%s] = \"%s\", \\\n", insn->upper, insn->name);
	}
	printf("}\n\n");
}