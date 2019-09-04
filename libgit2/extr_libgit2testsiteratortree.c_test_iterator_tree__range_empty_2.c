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
 int /*<<< orphan*/  tree_iterator_test (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_iterator_tree__range_empty_2(void)
{
	tree_iterator_test(
		"attr", "24fa9a9fc4e202313e24b648087495441dab432b",
		NULL, ".aaa_empty_before", 0, NULL);
}