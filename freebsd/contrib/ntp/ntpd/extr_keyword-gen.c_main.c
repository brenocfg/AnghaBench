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

/* Variables and functions */
 int debug ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  generate_fsm () ; 
 int /*<<< orphan*/  generate_preamble () ; 
 int /*<<< orphan*/  generate_token_text () ; 
 int /*<<< orphan*/  populate_symb (char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage:\n%s t_header.h\n", argv[0]);
		exit(1);
	}
	debug = 1;

	populate_symb(argv[1]);

	generate_preamble();
	generate_token_text();
	generate_fsm();

	return 0;
}