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
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_OBJECT_TAG ; 
 int /*<<< orphan*/  assert_peel_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void test_refs_peel__cannot_peel_into_a_non_existing_target(void)
{
	assert_peel_error(GIT_EINVALIDSPEC, "refs/tags/point_to_blob", GIT_OBJECT_TAG);
}