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
 int /*<<< orphan*/  expected_index_oids_range ; 
 int /*<<< orphan*/  expected_index_range ; 
 int /*<<< orphan*/  index_iterator_test (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_iterator_index__range(void)
{
	index_iterator_test(
		"attr", "root", "root", 0, ARRAY_SIZE(expected_index_range),
		expected_index_range, expected_index_oids_range);
}