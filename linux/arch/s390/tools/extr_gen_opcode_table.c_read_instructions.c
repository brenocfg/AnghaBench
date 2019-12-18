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
struct insn {int name_len; scalar_t__* name; int /*<<< orphan*/ * upper; int /*<<< orphan*/  format; int /*<<< orphan*/  type; int /*<<< orphan*/  opcode; } ;
struct gen_opcode {int nr; struct insn* insn; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insn_format_to_type (int /*<<< orphan*/ ) ; 
 struct insn* realloc (struct insn*,int) ; 
 int scanf (char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int strlen (scalar_t__*) ; 
 int /*<<< orphan*/  toupper (unsigned char) ; 

__attribute__((used)) static void read_instructions(struct gen_opcode *desc)
{
	struct insn insn;
	int rc, i;

	while (1) {
		rc = scanf("%s %s %s", insn.opcode, insn.name, insn.format);
		if (rc == EOF)
			break;
		if (rc != 3)
			exit(EXIT_FAILURE);
		insn.type = insn_format_to_type(insn.format);
		insn.name_len = strlen(insn.name);
		for (i = 0; i <= insn.name_len; i++)
			insn.upper[i] = toupper((unsigned char)insn.name[i]);
		desc->nr++;
		desc->insn = realloc(desc->insn, desc->nr * sizeof(*desc->insn));
		if (!desc->insn)
			exit(EXIT_FAILURE);
		desc->insn[desc->nr - 1] = insn;
	}
}