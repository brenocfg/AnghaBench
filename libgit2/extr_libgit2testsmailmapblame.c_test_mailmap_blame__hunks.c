#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ git_blame_options ;
struct TYPE_11__ {TYPE_1__* final_signature; int /*<<< orphan*/ * orig_signature; } ;
typedef  TYPE_3__ git_blame_hunk ;
struct TYPE_12__ {int /*<<< orphan*/  real_email; int /*<<< orphan*/  real_name; } ;
struct TYPE_9__ {int /*<<< orphan*/  email; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_4__*) ; 
 TYPE_2__ GIT_BLAME_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_BLAME_USE_MAILMAP ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_blame ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blame_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 TYPE_3__* git_blame_get_hunk_byline (int /*<<< orphan*/ ,size_t) ; 
 TYPE_4__* resolved ; 

void test_mailmap_blame__hunks(void)
{
	size_t idx = 0;
	const git_blame_hunk *hunk = NULL;
	git_blame_options opts = GIT_BLAME_OPTIONS_INIT;

	g_repo = cl_git_sandbox_init("mailmap");

	opts.flags |= GIT_BLAME_USE_MAILMAP;

	cl_git_pass(git_blame_file(&g_blame, g_repo, "file.txt", &opts));
	cl_assert(g_blame);

	for (idx = 0; idx < ARRAY_SIZE(resolved); ++idx) {
		hunk = git_blame_get_hunk_byline(g_blame, idx + 1);

		cl_assert(hunk->final_signature != NULL);
		cl_assert(hunk->orig_signature != NULL);
		cl_assert_equal_s(hunk->final_signature->name, resolved[idx].real_name);
		cl_assert_equal_s(hunk->final_signature->email, resolved[idx].real_email);
	}
}