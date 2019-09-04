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
 int /*<<< orphan*/  assert_is_branch (char*,int) ; 

void test_refs_read__can_determine_if_a_reference_is_a_local_branch(void)
{
	assert_is_branch("refs/heads/master", true);
	assert_is_branch("refs/heads/packed", true);
	assert_is_branch("refs/remotes/test/master", false);
	assert_is_branch("refs/tags/e90810b", false);
}