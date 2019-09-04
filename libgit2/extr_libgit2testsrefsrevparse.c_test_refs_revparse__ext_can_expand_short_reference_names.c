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
 int /*<<< orphan*/  test_object_and_ref (char*,char*,char*) ; 

void test_refs_revparse__ext_can_expand_short_reference_names(void)
{
	test_object_and_ref(
		"master",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"refs/heads/master");

	test_object_and_ref(
		"HEAD",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"refs/heads/master");

    test_object_and_ref(
		"tags/test",
		"b25fa35b38051e4ae45d4222e795f9df2e43f1d1",
        "refs/tags/test");
}