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
 int /*<<< orphan*/  test_object_and_ref (char*,char*,int /*<<< orphan*/ *) ; 

void test_refs_revparse__ext_returns_NULL_reference_when_expression_points_at_a_tree_content(void)
{
    test_object_and_ref(
		"tags/test:readme.txt",
		"0266163a49e280c4f5ed1e08facd36a2bd716bcf",
        NULL);
}