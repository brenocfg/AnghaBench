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
 int /*<<< orphan*/  GIT_SUBMODULE_RECURSE_NO ; 
 int /*<<< orphan*/  GIT_SUBMODULE_RECURSE_ONDEMAND ; 
 int /*<<< orphan*/  GIT_SUBMODULE_RECURSE_YES ; 
 int /*<<< orphan*/  assert_recurse_change (int /*<<< orphan*/ ) ; 

void test_submodule_modify__set_fetch_recurse_submodules(void)
{
	assert_recurse_change(GIT_SUBMODULE_RECURSE_YES);
	assert_recurse_change(GIT_SUBMODULE_RECURSE_NO);
	assert_recurse_change(GIT_SUBMODULE_RECURSE_ONDEMAND);
}