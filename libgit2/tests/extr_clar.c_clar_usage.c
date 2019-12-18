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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
clar_usage(const char *arg)
{
	printf("Usage: %s [options]\n\n", arg);
	printf("Options:\n");
	printf("  -sname        Run only the suite with `name` (can go to individual test name)\n");
	printf("  -iname        Include the suite with `name`\n");
	printf("  -xname        Exclude the suite with `name`\n");
	printf("  -v            Increase verbosity (show suite names)\n");
	printf("  -q            Only report tests that had an error\n");
	printf("  -Q            Quit as soon as a test fails\n");
	printf("  -l            Print suite names\n");
	printf("  -r[filename]  Write summary file (to the optional filename)\n");
	exit(-1);
}