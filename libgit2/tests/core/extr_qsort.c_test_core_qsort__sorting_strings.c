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
 int /*<<< orphan*/  assert_sorted (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_str ; 

void test_core_qsort__sorting_strings(void)
{
	char *a[] = { "foo", "bar", "baz" };
	assert_sorted(a, cmp_str);
}