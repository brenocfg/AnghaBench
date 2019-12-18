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
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  assert_peel_generic (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_peel_repo ; 

void test_refs_peel__can_peel_fully_peeled_packed_refs(void)
{
	assert_peel_generic(g_peel_repo,
			    "refs/tags/tag-inside-tags", GIT_OBJECT_ANY,
			    "0df1a5865c8abfc09f1f2182e6a31be550e99f07",
			    GIT_OBJECT_COMMIT);
	assert_peel_generic(g_peel_repo,
			    "refs/foo/tag-outside-tags", GIT_OBJECT_ANY,
			    "0df1a5865c8abfc09f1f2182e6a31be550e99f07",
			    GIT_OBJECT_COMMIT);
}