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
struct TYPE_5__ {int /*<<< orphan*/  orig_path; } ;
typedef  TYPE_1__ git_blame_hunk ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_p (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_blame ; 
 TYPE_1__* git_blame_get_hunk_byindex (int /*<<< orphan*/ ,int) ; 

void test_blame_getters__byindex(void)
{
	const git_blame_hunk *h = git_blame_get_hunk_byindex(g_blame, 2);
	cl_assert(h);
	cl_assert_equal_s(h->orig_path, "c");

	h = git_blame_get_hunk_byindex(g_blame, 95);
	cl_assert_equal_p(h, NULL);
}