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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *msg, const char *arg)
{
	fputs("usage: remote add <name> <url>\n", stderr);
	fputs("       remote remove <name>\n", stderr);
	fputs("       remote rename <old> <new>\n", stderr);
	fputs("       remote set-url [--push] <name> <newurl>\n", stderr);
	fputs("       remote show [-v|--verbose]\n", stderr);

	if (msg && !arg)
		fprintf(stderr, "\n%s\n", msg);
	else if (msg && arg)
		fprintf(stderr, "\n%s: %s\n", msg, arg);
	exit(1);
}