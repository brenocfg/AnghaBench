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
 int /*<<< orphan*/  assert_matches (char*,char*,int,int,int,int) ; 

void test_core_wildmatch__case_sensitivity(void)
{
	assert_matches("a", "[A-Z]", 0, 1, 0, 1);
	assert_matches("A", "[A-Z]", 1, 1, 1, 1);
	assert_matches("A", "[a-z]", 0, 1, 0, 1);
	assert_matches("a", "[a-z]", 1, 1, 1, 1);
	assert_matches("a", "[[:upper:]]", 0, 1, 0, 1);
	assert_matches("A", "[[:upper:]]", 1, 1, 1, 1);
	assert_matches("A", "[[:lower:]]", 0, 1, 0, 1);
	assert_matches("a", "[[:lower:]]", 1, 1, 1, 1);
	assert_matches("A", "[B-Za]", 0, 1, 0, 1);
	assert_matches("a", "[B-Za]", 1, 1, 1, 1);
	assert_matches("A", "[B-a]", 0, 1, 0, 1);
	assert_matches("a", "[B-a]", 1, 1, 1, 1);
	assert_matches("z", "[Z-y]", 0, 1, 0, 1);
	assert_matches("Z", "[Z-y]", 1, 1, 1, 1);
}