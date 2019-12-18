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
 int /*<<< orphan*/  test_invalid_name (char*) ; 

void test_refs_create__creating_a_reference_with_an_invalid_name_returns_EINVALIDSPEC(void)
{
	test_invalid_name("refs/heads/inv@{id");
	test_invalid_name("refs/heads/back\\slash");

	test_invalid_name("refs/heads/foo ");
	test_invalid_name("refs/heads/foo /bar");
	test_invalid_name("refs/heads/com1:bar/foo");

	test_invalid_name("refs/heads/e:");
	test_invalid_name("refs/heads/c:/foo");

	test_invalid_name("refs/heads/foo.");
}