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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(char * progname) {
	printf("%s: tests libutil humanize_number function\n", progname);
	printf("Usage: %s [-nE] [-l num] [-v]\n\n", progname);
	printf("Options:\n");
	printf("\t-l num\tSet max length for result; buflen = num + 1\n");
	printf("\t\t  (NOTE: does not change expected result strings.)\n");
	printf("\t-n\tInclude negative scale tests, which cause older libutil\n");
	printf("\t\t  version of function to coredump with assertion failure\n");
	printf("\t-E\tInclude numbers > 1/2 Exa[byte] which currently fail\n");
	printf("\t-v\tVerbose - always print summary results\n");
	printf("\t-h, -?\tShow options\n");
}