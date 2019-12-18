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
struct insn {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_INSN_SIZE ; 
 int /*<<< orphan*/  dump_insn (int /*<<< orphan*/ *,struct insn*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  input_file ; 
 char* prog ; 
 int seed ; 

__attribute__((used)) static void dump_stream(FILE *fp, const char *msg, unsigned long nr_iter,
			unsigned char *insn_buff, struct insn *insn)
{
	int i;

	fprintf(fp, "%s:\n", msg);

	dump_insn(fp, insn);

	fprintf(fp, "You can reproduce this with below command(s);\n");

	/* Input a decoded instruction sequence directly */
	fprintf(fp, " $ echo ");
	for (i = 0; i < MAX_INSN_SIZE; i++)
		fprintf(fp, " %02x", insn_buff[i]);
	fprintf(fp, " | %s -i -\n", prog);

	if (!input_file) {
		fprintf(fp, "Or \n");
		/* Give a seed and iteration number */
		fprintf(fp, " $ %s -s 0x%x,%lu\n", prog, seed, nr_iter);
	}
}