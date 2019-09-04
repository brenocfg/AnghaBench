#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; } ;
typedef  TYPE_1__ git_repository_init_options ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_REPOSITORY_INIT_BARE ; 
 int GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE ; 
 int GIT_REPOSITORY_INIT_MKPATH ; 
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  configure_templatedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_init_ext (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 
 int /*<<< orphan*/  template_sandbox (char*) ; 
 int /*<<< orphan*/  validate_templates (int /*<<< orphan*/ ,char*) ; 

void test_repo_init__external_templates_with_leading_dot(void)
{
	git_buf template_path = GIT_BUF_INIT;

	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;

	cl_set_cleanup(&cleanup_repository, "templated.git");
	template_sandbox("template");

	cl_must_pass(p_rename("template", ".template_with_leading_dot"));

	cl_git_pass(git_buf_joinpath(&template_path, clar_sandbox_path(),
		".template_with_leading_dot"));

	configure_templatedir(template_path.ptr);

	opts.flags = GIT_REPOSITORY_INIT_MKPATH | GIT_REPOSITORY_INIT_BARE |
		GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE;

	cl_git_pass(git_repository_init_ext(&_repo, "templated.git", &opts));

	validate_templates(_repo, ".template_with_leading_dot");
	cl_fixture_cleanup(".template_with_leading_dot");

	git_buf_dispose(&template_path);
}