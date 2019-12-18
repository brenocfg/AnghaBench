#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int member_0; } ;
struct TYPE_6__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_map ; 
 int /*<<< orphan*/  git_oidmap_get (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_oidmap_set (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 

void test_core_oidmap__setting_oid_persists(void)
{
	git_oid oids[] = {
	    {{ 0x01 }},
	    {{ 0x02 }},
	    {{ 0x03 }}
	};

	cl_git_pass(git_oidmap_set(g_map, &oids[0], "one"));
	cl_git_pass(git_oidmap_set(g_map, &oids[1], "two"));
	cl_git_pass(git_oidmap_set(g_map, &oids[2], "three"));

	cl_assert_equal_s(git_oidmap_get(g_map, &oids[0]), "one");
	cl_assert_equal_s(git_oidmap_get(g_map, &oids[1]), "two");
	cl_assert_equal_s(git_oidmap_get(g_map, &oids[2]), "three");
}