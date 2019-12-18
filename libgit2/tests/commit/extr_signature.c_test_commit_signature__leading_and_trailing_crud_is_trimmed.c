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

void test_commit_signature__leading_and_trailing_crud_is_trimmed(void)
{
	assert_name_and_email("nulltoken", "emeric.fermas@gmail.com", "\"nulltoken\"", "\"emeric.fermas@gmail.com\"");
	assert_name_and_email("nulltoken w", "emeric.fermas@gmail.com", "nulltoken w.", "emeric.fermas@gmail.com");
	assert_name_and_email("nulltoken \xe2\x98\xba", "emeric.fermas@gmail.com", "nulltoken \xe2\x98\xba", "emeric.fermas@gmail.com");
}