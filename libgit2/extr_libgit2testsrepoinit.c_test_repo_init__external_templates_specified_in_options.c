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
struct TYPE_4__ {int flags; char* template_path; } ;
typedef  TYPE_1__ git_repository_init_options ;

/* Variables and functions */
 int GIT_REPOSITORY_INIT_BARE ; 
 int GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE ; 
 int GIT_REPOSITORY_INIT_MKPATH ; 
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  git__suffixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_init_ext (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  template_sandbox (char*) ; 
 int /*<<< orphan*/  validate_templates (int /*<<< orphan*/ ,char*) ; 

void test_repo_init__external_templates_specified_in_options(void)
{
	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;

	cl_set_cleanup(&cleanup_repository, "templated.git");
	template_sandbox("template");

	opts.flags = GIT_REPOSITORY_INIT_MKPATH | GIT_REPOSITORY_INIT_BARE |
		GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE;
	opts.template_path = "template";

	cl_git_pass(git_repository_init_ext(&_repo, "templated.git", &opts));

	cl_assert(git_repository_is_bare(_repo));

	cl_assert(!git__suffixcmp(git_repository_path(_repo), "/templated.git/"));

	validate_templates(_repo, "template");
	cl_fixture_cleanup("template");
}