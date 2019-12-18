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
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_OPT_SET_SEARCH_PATH ; 
 TYPE_1__ _global_path ; 
 int /*<<< orphan*/ * _repo ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 char* fixture_repo ; 
 char* fixture_templates ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 

void test_repo_template__cleanup(void)
{
	git_libgit2_opts(GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL,
		_global_path.ptr);
	git_buf_dispose(&_global_path);

	cl_fixture_cleanup("tmp_global_path");

	if (fixture_repo) {
		cl_fixture_cleanup(fixture_repo);
		fixture_repo = NULL;
	}

	if (fixture_templates) {
		cl_fixture_cleanup(fixture_templates);
		fixture_templates = NULL;
	}

	git_repository_free(_repo);
	_repo = NULL;
}