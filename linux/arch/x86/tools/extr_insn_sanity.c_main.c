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
struct insn {scalar_t__ next_byte; scalar_t__ kaddr; } ;
typedef  int /*<<< orphan*/  insn_buff ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_NOP ; 
 int MAX_INSN_SIZE ; 
 int /*<<< orphan*/  dump_insn (int /*<<< orphan*/ ,struct insn*) ; 
 int /*<<< orphan*/  dump_stream (int /*<<< orphan*/ ,char*,unsigned long,unsigned char*,struct insn*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,int,char*,int,int) ; 
 scalar_t__ generate_insn (unsigned char*) ; 
 scalar_t__ input_file ; 
 int /*<<< orphan*/  insn_complete (struct insn*) ; 
 int /*<<< orphan*/  insn_get_length (struct insn*) ; 
 int /*<<< orphan*/  insn_init (struct insn*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 unsigned long iter_end ; 
 unsigned long iter_start ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_args (int,char**) ; 
 char* prog ; 
 int seed ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int verbose ; 
 int /*<<< orphan*/  x86_64 ; 

int main(int argc, char **argv)
{
	struct insn insn;
	int insns = 0;
	int errors = 0;
	unsigned long i;
	unsigned char insn_buff[MAX_INSN_SIZE * 2];

	parse_args(argc, argv);

	/* Prepare stop bytes with NOPs */
	memset(insn_buff + MAX_INSN_SIZE, INSN_NOP, MAX_INSN_SIZE);

	for (i = 0; i < iter_end; i++) {
		if (generate_insn(insn_buff) <= 0)
			break;

		if (i < iter_start)	/* Skip to given iteration number */
			continue;

		/* Decode an instruction */
		insn_init(&insn, insn_buff, sizeof(insn_buff), x86_64);
		insn_get_length(&insn);

		if (insn.next_byte <= insn.kaddr ||
		    insn.kaddr + MAX_INSN_SIZE < insn.next_byte) {
			/* Access out-of-range memory */
			dump_stream(stderr, "Error: Found an access violation", i, insn_buff, &insn);
			errors++;
		} else if (verbose && !insn_complete(&insn))
			dump_stream(stdout, "Info: Found an undecodable input", i, insn_buff, &insn);
		else if (verbose >= 2)
			dump_insn(stdout, &insn);
		insns++;
	}

	fprintf((errors) ? stderr : stdout,
		"%s: %s: decoded and checked %d %s instructions with %d errors (seed:0x%x)\n",
		prog,
		(errors) ? "Failure" : "Success",
		insns,
		(input_file) ? "given" : "random",
		errors,
		seed);

	return errors ? 1 : 0;
}