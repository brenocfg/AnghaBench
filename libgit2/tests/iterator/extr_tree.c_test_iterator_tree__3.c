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
 int /*<<< orphan*/  expected_tree_3 ; 
 int /*<<< orphan*/  tree_iterator_test (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void test_iterator_tree__3(void)
{
	tree_iterator_test("status", "0017bd4ab1e", NULL, NULL, 8, expected_tree_3);
}