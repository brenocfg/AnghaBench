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
struct TYPE_4__ {int flags; char* template_path; int mode; } ;
typedef  TYPE_1__ git_repository_init_options ;

/* Variables and functions */
 int GIT_FILEMODE_BLOB ; 
 int GIT_FILEMODE_TREE ; 
 int GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE ; 
 int GIT_REPOSITORY_INIT_MKPATH ; 
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int GIT_REPOSITORY_INIT_SHARED_GROUP ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  assert_mode_seems_okay (char const*,char*,int,int,int) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int cl_repo_get_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  git__suffixcmp (char*,char*) ; 
 int /*<<< orphan*/  git_repository_init_ext (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ ) ; 
 char* git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  template_sandbox (char*) ; 
 int /*<<< orphan*/  validate_templates (int /*<<< orphan*/ ,char*) ; 

void test_repo_init__extended_with_template_and_shared_mode(void)
{
	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;
	int filemode = true;
	const char *repo_path = NULL;

	cl_set_cleanup(&cleanup_repository, "init_shared_from_tpl");
	template_sandbox("template");

	opts.flags = GIT_REPOSITORY_INIT_MKPATH |
		GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE;
	opts.template_path = "template";
	opts.mode = GIT_REPOSITORY_INIT_SHARED_GROUP;

	cl_git_pass(git_repository_init_ext(&_repo, "init_shared_from_tpl", &opts));

	cl_assert(!git_repository_is_bare(_repo));
	cl_assert(!git__suffixcmp(git_repository_path(_repo), "/init_shared_from_tpl/.git/"));

	filemode = cl_repo_get_bool(_repo, "core.filemode");

	repo_path = git_repository_path(_repo);
	assert_mode_seems_okay(repo_path, "hooks",
		GIT_FILEMODE_TREE | GIT_REPOSITORY_INIT_SHARED_GROUP, true, filemode);
	assert_mode_seems_okay(repo_path, "info",
		GIT_FILEMODE_TREE | GIT_REPOSITORY_INIT_SHARED_GROUP, true, filemode);
	assert_mode_seems_okay(repo_path, "description",
		GIT_FILEMODE_BLOB, false, filemode);

	validate_templates(_repo, "template");

	cl_fixture_cleanup("template");
}