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
 int GIT_REVPARSE_MERGE_BASE ; 
 int GIT_REVPARSE_RANGE ; 
 int GIT_REVPARSE_SINGLE ; 
 int /*<<< orphan*/  test_id (char*,char*,char*,int) ; 
 int /*<<< orphan*/  test_invalid_revspec (char*) ; 

void test_refs_revparse__parses_range_operator(void)
{
	test_id("HEAD", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750", NULL, GIT_REVPARSE_SINGLE);
	test_id("HEAD~3..HEAD",
		"4a202b346bb0fb0db7eff3cffeb3c70babbd2045",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		GIT_REVPARSE_RANGE);

	test_id("HEAD~3...HEAD",
		"4a202b346bb0fb0db7eff3cffeb3c70babbd2045",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		GIT_REVPARSE_RANGE | GIT_REVPARSE_MERGE_BASE);

	test_id("HEAD~3..",
		"4a202b346bb0fb0db7eff3cffeb3c70babbd2045",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		GIT_REVPARSE_RANGE);

	test_id("HEAD~3...",
		"4a202b346bb0fb0db7eff3cffeb3c70babbd2045",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		GIT_REVPARSE_RANGE | GIT_REVPARSE_MERGE_BASE);

	test_id("..HEAD~3",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"4a202b346bb0fb0db7eff3cffeb3c70babbd2045",
		GIT_REVPARSE_RANGE);

	test_id("...HEAD~3",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"4a202b346bb0fb0db7eff3cffeb3c70babbd2045",
		GIT_REVPARSE_RANGE | GIT_REVPARSE_MERGE_BASE);

	test_id("...",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		GIT_REVPARSE_RANGE | GIT_REVPARSE_MERGE_BASE);

	test_invalid_revspec("..");
}