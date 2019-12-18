#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  automergeable_id ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_branch () ; 
 int /*<<< orphan*/  repo_index ; 
 int /*<<< orphan*/  set_gitattributes_to (char*) ; 
 int /*<<< orphan*/  test_drivers_register () ; 
 int /*<<< orphan*/  test_drivers_unregister () ; 

void test_merge_driver__not_configured_driver_falls_back(void)
{
	const git_index_entry *idx;

	test_drivers_unregister();

	/* `merge` without specifying a driver indicates `text` */
	set_gitattributes_to("notfound");

	merge_branch();

	cl_assert((idx = git_index_get_bypath(repo_index, "automergeable.txt", 0)));
	cl_assert_equal_oid(&automergeable_id, &idx->id);

	test_drivers_register();
}