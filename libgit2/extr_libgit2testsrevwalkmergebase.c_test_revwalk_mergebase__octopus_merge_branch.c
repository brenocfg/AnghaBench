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
 int /*<<< orphan*/  assert_mergebase_octopus (char*,int,char*,char*,char*) ; 

void test_revwalk_mergebase__octopus_merge_branch(void)
{
	assert_mergebase_octopus("8496071c1b46c854b31185ea97743be6a8774479", 3, "a65fed", "763d71", "849607");

	assert_mergebase_octopus("8496071c1b46c854b31185ea97743be6a8774479", 3, "a65fed", "763d71", "849607");
	assert_mergebase_octopus("8496071c1b46c854b31185ea97743be6a8774479", 3, "a65fed", "849607", "763d71");
	assert_mergebase_octopus("8496071c1b46c854b31185ea97743be6a8774479", 3, "849607", "a65fed", "763d71");
}