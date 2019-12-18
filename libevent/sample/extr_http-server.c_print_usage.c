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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void
print_usage(FILE *out, const char *prog, int exit_code)
{
	fprintf(out,
		"Syntax: %s [ OPTS ] <docroot>\n"
		" -p      - port\n"
		" -U      - bind to unix socket\n"
		" -u      - unlink unix socket before bind\n"
		" -I      - IOCP\n"
		" -v      - verbosity, enables libevent debug logging too\n", prog);
	exit(exit_code);
}