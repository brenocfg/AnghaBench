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
 int /*<<< orphan*/  assert_invalid_single_spec (char*) ; 
 int /*<<< orphan*/  test_object (char*,char*) ; 

void test_refs_revparse__previous_head(void)
{
	assert_invalid_single_spec("@{-xyz}");
	assert_invalid_single_spec("@{-0}");
	assert_invalid_single_spec("@{-1b}");

	test_object("@{-42}", NULL);

	test_object("@{-2}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	test_object("@{-1}", "a4a7dce85cf63874e984719f4fdd239f5145052f");
}