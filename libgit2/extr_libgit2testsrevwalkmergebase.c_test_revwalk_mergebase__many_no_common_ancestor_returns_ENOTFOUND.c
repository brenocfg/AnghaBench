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
 int /*<<< orphan*/  assert_mergebase_many (int /*<<< orphan*/ *,int,char*,char*,char*) ; 

void test_revwalk_mergebase__many_no_common_ancestor_returns_ENOTFOUND(void)
{
	assert_mergebase_many(NULL, 3, "41bc8c", "e90810", "a65fed");
	assert_mergebase_many(NULL, 3, "e90810", "41bc8c", "a65fed");
	assert_mergebase_many(NULL, 3, "e90810", "a65fed", "41bc8c");
	assert_mergebase_many(NULL, 3, "a65fed", "e90810", "41bc8c");
	assert_mergebase_many(NULL, 3, "a65fed", "41bc8c", "e90810");

	assert_mergebase_many(NULL, 3, "e90810", "763d71", "a65fed");
}