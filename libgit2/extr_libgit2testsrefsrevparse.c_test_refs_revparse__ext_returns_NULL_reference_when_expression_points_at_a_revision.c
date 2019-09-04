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
 int /*<<< orphan*/  test_object_and_ref (char*,char*,int /*<<< orphan*/ *) ; 

void test_refs_revparse__ext_returns_NULL_reference_when_expression_points_at_a_revision(void)
{
    test_object_and_ref(
        "HEAD~3",
        "4a202b346bb0fb0db7eff3cffeb3c70babbd2045",
        NULL);

    test_object_and_ref(
        "HEAD~0",
        "a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
        NULL);

    test_object_and_ref(
        "HEAD^0",
        "a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
        NULL);

    test_object_and_ref(
		"@{-1}@{0}",
		"a4a7dce85cf63874e984719f4fdd239f5145052f",
		NULL);
}