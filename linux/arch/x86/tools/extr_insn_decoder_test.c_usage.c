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
 char* prog ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(void)
{
	fprintf(stderr, "Usage: objdump -d a.out | awk -f objdump_reformat.awk"
		" | %s [-y|-n] [-v]\n", prog);
	fprintf(stderr, "\t-y	64bit mode\n");
	fprintf(stderr, "\t-n	32bit mode\n");
	fprintf(stderr, "\t-v	verbose mode\n");
	exit(1);
}