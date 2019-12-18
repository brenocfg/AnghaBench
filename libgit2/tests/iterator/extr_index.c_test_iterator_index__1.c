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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expected_index_1 ; 
 int /*<<< orphan*/  expected_index_oids_1 ; 
 int /*<<< orphan*/  index_iterator_test (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_iterator_index__1(void)
{
	index_iterator_test(
		"status", NULL, NULL, 0, ARRAY_SIZE(expected_index_1),
		expected_index_1, expected_index_oids_1);
}