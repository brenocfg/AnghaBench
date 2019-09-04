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
 int /*<<< orphan*/  assert_name_and_email (char*,char*,char*,char*) ; 

void test_commit_signature__create_two_char(void)
{
	/* creating a two character signature */
	assert_name_and_email("xx", "foo@bar.baz", "xx", "foo@bar.baz");
}