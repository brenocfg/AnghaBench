#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_map ; 
 int git_oidmap_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oidmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oidmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* test_oids ; 

void test_core_oidmap__basic(void)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(test_oids); ++i) {
		cl_assert(!git_oidmap_exists(g_map, &test_oids[i].oid));
		cl_git_pass(git_oidmap_set(g_map, &test_oids[i].oid, &test_oids[i]));
	}

	for (i = 0; i < ARRAY_SIZE(test_oids); ++i) {
		cl_assert(git_oidmap_exists(g_map, &test_oids[i].oid));
		cl_assert_equal_p(git_oidmap_get(g_map, &test_oids[i].oid), &test_oids[i]);
	}
}