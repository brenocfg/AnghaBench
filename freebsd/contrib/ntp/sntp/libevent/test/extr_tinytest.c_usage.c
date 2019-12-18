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
struct testgroup_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  tinytest_set_flag_ (struct testgroup_t*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usage(struct testgroup_t *groups, int list_groups)
{
	puts("Options are: [--verbose|--quiet|--terse] [--no-fork]");
	puts("  Specify tests by name, or using a prefix ending with '..'");
	puts("  To skip a test, prefix its name with a colon.");
	puts("  To enable a disabled test, prefix its name with a plus.");
	puts("  Use --list-tests for a list of tests.");
	if (list_groups) {
		puts("Known tests are:");
		tinytest_set_flag_(groups, "..", 1, 0);
	}
	exit(0);
}