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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  fprintf__simple_string () ; 
 int /*<<< orphan*/  snprintf__overflow () ; 
 int /*<<< orphan*/  snprintf__two_formatters () ; 

int
main(void)
{
	/* If you have read the printf_test.c counterpart in the atf/
	 * directory, you may think that the sequencing of tests below and
	 * the exposed behavior to the user is very similar.  But you'd be
	 * wrong.
	 *
	 * There are two major differences with this and the ATF version.
	 * The first is that the code below has no provisions to detect
	 * failures in one test and continue running the other tests: the
	 * first failure causes the whole test program to exit.  The second
	 * is that this particular main() has no arguments: without ATF,
	 * all test programs may expose a different command-line interface,
	 * and this is an issue for consistency purposes. */
	snprintf__two_formatters();
	snprintf__overflow();
	fprintf__simple_string();

	return EXIT_SUCCESS;
}