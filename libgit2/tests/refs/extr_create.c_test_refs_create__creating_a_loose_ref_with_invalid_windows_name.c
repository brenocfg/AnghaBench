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
 int /*<<< orphan*/  test_win32_name (char*) ; 

void test_refs_create__creating_a_loose_ref_with_invalid_windows_name(void)
{
	test_win32_name("refs/heads/foo./bar");

	test_win32_name("refs/heads/aux");
	test_win32_name("refs/heads/aux.foo/bar");

	test_win32_name("refs/heads/com1");
}