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
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  assert_config_entry_on_init_bytype (char const*,int,int) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assert_config_entry_on_init(
	const char *config_key, int expected_value)
{
	assert_config_entry_on_init_bytype(config_key, expected_value, true);
	git_repository_free(_repo);

	assert_config_entry_on_init_bytype(config_key, expected_value, false);
}