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
 int /*<<< orphan*/  expected_tree_ranged_1 ; 
 int /*<<< orphan*/  tree_iterator_test (char*,char*,char*,char*,int,int /*<<< orphan*/ ) ; 

void test_iterator_tree__ranged_1(void)
{
	tree_iterator_test(
		"attr", "24fa9a9fc4e202313e24b648087495441dab432b",
		"sub/subdir_test2.txt", "sub/subdir_test2.txt",
		1, expected_tree_ranged_1);
}