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
struct expected_entry {char* member_0; char* member_1; int /*<<< orphan*/  member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_config_contains_all (int /*<<< orphan*/ ,struct expected_entry*) ; 
 int /*<<< orphan*/  backend ; 
 int /*<<< orphan*/  setup_backend (char*) ; 

void test_config_memory__foreach_sees_multivar(void)
{
	struct expected_entry entries[] = {
		{ "general.foo", "bar1", 0 },
		{ "general.foo", "bar2", 0 },
		{ NULL, NULL, 0 },
	};

	setup_backend(
		"[general]\n"
		"foo=bar1\n"
		"foo=bar2\n");
	assert_config_contains_all(backend, entries);
}