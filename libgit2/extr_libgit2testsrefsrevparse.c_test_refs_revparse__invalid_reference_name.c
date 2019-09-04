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
 int /*<<< orphan*/  assert_invalid_single_spec (char*) ; 

void test_refs_revparse__invalid_reference_name(void)
{
	assert_invalid_single_spec("this doesn't make sense");
	assert_invalid_single_spec("Inv@{id");
	assert_invalid_single_spec("");
}