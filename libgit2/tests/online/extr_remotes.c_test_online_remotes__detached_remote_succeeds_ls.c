#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_remote_head ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  URL ; 
 int /*<<< orphan*/  cl_assert_ (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (size_t,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create_detached (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_ls (TYPE_1__ const***,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

void test_online_remotes__detached_remote_succeeds_ls(void)
{
	const char *refs[] = {
	    "HEAD",
	    "refs/heads/first-merge",
	    "refs/heads/master",
	    "refs/heads/no-parent",
	    "refs/tags/annotated_tag",
	    "refs/tags/annotated_tag^{}",
	    "refs/tags/blob",
	    "refs/tags/commit_tree",
	    "refs/tags/nearly-dangling",
	};
	const git_remote_head **heads;
	git_remote *remote;
	size_t i, j, n;

	cl_git_pass(git_remote_create_detached(&remote, URL));
	cl_git_pass(git_remote_connect(remote, GIT_DIRECTION_FETCH, NULL, NULL, NULL));
	cl_git_pass(git_remote_ls(&heads, &n, remote));

	cl_assert_equal_sz(n, 9);
	for (i = 0; i < n; i++) {
		char found = false;

		for (j = 0; j < ARRAY_SIZE(refs); j++) {
			if (!strcmp(heads[i]->name, refs[j])) {
				found = true;
				break;
			}
		}

		cl_assert_(found, heads[i]->name);
	}

	git_remote_free(remote);
}