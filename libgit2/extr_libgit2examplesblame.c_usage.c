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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *msg, const char *arg)
{
	if (msg && arg)
		fprintf(stderr, "%s: %s\n", msg, arg);
	else if (msg)
		fprintf(stderr, "%s\n", msg);
	fprintf(stderr, "usage: blame [options] [<commit range>] <path>\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "   <commit range>      example: `HEAD~10..HEAD`, or `1234abcd`\n");
	fprintf(stderr, "   -L <n,m>            process only line range n-m, counting from 1\n");
	fprintf(stderr, "   -M                  find line moves within and across files\n");
	fprintf(stderr, "   -C                  find line copies within and across files\n");
	fprintf(stderr, "   -F                  follow only the first parent commits\n");
	fprintf(stderr, "\n");
	exit(1);
}