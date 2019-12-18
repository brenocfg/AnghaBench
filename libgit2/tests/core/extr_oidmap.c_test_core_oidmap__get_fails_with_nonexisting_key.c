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
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_map ; 
 int /*<<< orphan*/  git_oidmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oidmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* test_oids ; 

void test_core_oidmap__get_fails_with_nonexisting_key(void)
{
	size_t i;

	/* Do _not_ add last OID to verify that we cannot look it up */
	for (i = 0; i < ARRAY_SIZE(test_oids) - 1; ++i)
		cl_git_pass(git_oidmap_set(g_map, &test_oids[i].oid, &test_oids[i]));

	cl_assert_equal_p(git_oidmap_get(g_map, &test_oids[ARRAY_SIZE(test_oids) - 1].oid), NULL);
}