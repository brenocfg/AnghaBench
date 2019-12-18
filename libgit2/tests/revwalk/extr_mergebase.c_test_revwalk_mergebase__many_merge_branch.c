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
 int /*<<< orphan*/  assert_mergebase_many (char*,int,char*,char*,char*,...) ; 

void test_revwalk_mergebase__many_merge_branch(void)
{
	assert_mergebase_many("c47800c7266a2be04c571c04d5a6614691ea99bd", 3, "a65fed", "763d71", "849607");

	assert_mergebase_many("c47800c7266a2be04c571c04d5a6614691ea99bd", 3, "763d71", "e90810", "a65fed");
	assert_mergebase_many("c47800c7266a2be04c571c04d5a6614691ea99bd", 3, "763d71", "a65fed", "e90810");

	assert_mergebase_many("c47800c7266a2be04c571c04d5a6614691ea99bd", 3, "a65fed", "763d71", "849607");
	assert_mergebase_many("c47800c7266a2be04c571c04d5a6614691ea99bd", 3, "a65fed", "849607", "763d71");
	assert_mergebase_many("8496071c1b46c854b31185ea97743be6a8774479", 3, "849607", "a65fed", "763d71");

	assert_mergebase_many("5b5b025afb0b4c913b4c338a42934a3863bf3644", 5, "5b5b02", "763d71", "a4a7dc", "a65fed", "41bc8c");
}