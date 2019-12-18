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
 int /*<<< orphan*/  assert_is_tag (char*,int) ; 

void test_refs_read__can_determine_if_a_reference_is_a_tag(void)
{
	assert_is_tag("refs/tags/e90810b", true);
	assert_is_tag("refs/tags/test", true);
	assert_is_tag("refs/heads/packed", false);
	assert_is_tag("refs/remotes/test/master", false);
}