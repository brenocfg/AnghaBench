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
 int /*<<< orphan*/  GIT_SUBMODULE_UPDATE_CHECKOUT ; 
 int /*<<< orphan*/  GIT_SUBMODULE_UPDATE_NONE ; 
 int /*<<< orphan*/  GIT_SUBMODULE_UPDATE_REBASE ; 
 int /*<<< orphan*/  assert_update_change (int /*<<< orphan*/ ) ; 

void test_submodule_modify__set_update(void)
{
	assert_update_change(GIT_SUBMODULE_UPDATE_REBASE);
	assert_update_change(GIT_SUBMODULE_UPDATE_NONE);
	assert_update_change(GIT_SUBMODULE_UPDATE_CHECKOUT);
}