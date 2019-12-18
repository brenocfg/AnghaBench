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
 int /*<<< orphan*/  assert_absent (char*,char*) ; 

void test_core_memmem__edgecases(void)
{
	assert_absent(NULL, NULL);
	assert_absent("a", NULL);
	assert_absent(NULL, "a");
	assert_absent("", "a");
	assert_absent("a", "");
}