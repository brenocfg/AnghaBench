#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_6__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string (char const**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_path_dirname_r (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_head_detached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 char const* git_submodule_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_fixture_submodule_simple () ; 

void test_submodule_init__relative_url_detached_head(void)
{
	git_submodule *sm;
	git_config *cfg;
	git_buf absolute_url = GIT_BUF_INIT;
	const char *config_url;
	git_reference *head_ref = NULL;
	git_object *head_commit = NULL;

	g_repo = setup_fixture_submodule_simple();

	/* Put the parent repository into a detached head state. */
	cl_git_pass(git_repository_head(&head_ref, g_repo));
	cl_git_pass(git_reference_peel(&head_commit, head_ref, GIT_OBJECT_COMMIT));

	cl_git_pass(git_repository_set_head_detached(g_repo, git_commit_id((git_commit *)head_commit)));

	cl_assert(git_path_dirname_r(&absolute_url, git_repository_workdir(g_repo)) > 0);
	cl_git_pass(git_buf_joinpath(&absolute_url, absolute_url.ptr, "testrepo.git"));

	cl_git_pass(git_submodule_lookup(&sm, g_repo, "testrepo"));

	/* verify that the .gitmodules is set with an absolute path*/
	cl_assert_equal_s("../testrepo.git", git_submodule_url(sm));

	/* init and verify that absolute path is written to .git/config */
	cl_git_pass(git_submodule_init(sm, false));

	cl_git_pass(git_repository_config_snapshot(&cfg, g_repo));

	cl_git_pass(git_config_get_string(&config_url, cfg, "submodule.testrepo.url"));
	cl_assert_equal_s(absolute_url.ptr, config_url);

	git_buf_dispose(&absolute_url);
	git_config_free(cfg);
	git_object_free(head_commit);
	git_reference_free(head_ref);
	git_submodule_free(sm);
}