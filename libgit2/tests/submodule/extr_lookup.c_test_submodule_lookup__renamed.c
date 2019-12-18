#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int count; } ;
typedef  TYPE_2__ sm_lookup_data ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int mode; char const* path; int /*<<< orphan*/  id; TYPE_1__ member_0; } ;
typedef  TYPE_3__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int GIT_FILEMODE_COMMIT ; 
 int /*<<< orphan*/  cl_assert (TYPE_3__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_remove (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 
 int /*<<< orphan*/  sm_lookup_cb ; 

void test_submodule_lookup__renamed(void)
{
	const char *newpath = "sm_actually_changed";
	git_index *idx;
	sm_lookup_data data;

	cl_git_pass(git_repository_index__weakptr(&idx, g_repo));

	/* We're replicating 'git mv sm_unchanged sm_actually_changed' in this test */

	cl_git_pass(p_rename("submod2/sm_unchanged", "submod2/sm_actually_changed"));

	/* Change the path in .gitmodules and stage it*/
	{
		git_config *cfg;

		cl_git_pass(git_config_open_ondisk(&cfg, "submod2/.gitmodules"));
		cl_git_pass(git_config_set_string(cfg, "submodule.sm_unchanged.path", newpath));
		git_config_free(cfg);

		cl_git_pass(git_index_add_bypath(idx, ".gitmodules"));
	}

	/* Change the worktree info in the submodule's config */
	{
		git_config *cfg;

		cl_git_pass(git_config_open_ondisk(&cfg, "submod2/.git/modules/sm_unchanged/config"));
		cl_git_pass(git_config_set_string(cfg, "core.worktree", "../../../sm_actually_changed"));
		git_config_free(cfg);
	}

	/* Rename the entry in the index */
	{
		const git_index_entry *e;
		git_index_entry entry = {{ 0 }};

		e = git_index_get_bypath(idx, "sm_unchanged", 0);
		cl_assert(e);
		cl_assert_equal_i(GIT_FILEMODE_COMMIT, e->mode);

		entry.path = newpath;
		entry.mode = GIT_FILEMODE_COMMIT;
		git_oid_cpy(&entry.id, &e->id);

		cl_git_pass(git_index_remove(idx, "sm_unchanged", 0));
		cl_git_pass(git_index_add(idx, &entry));
		cl_git_pass(git_index_write(idx));
	}

	memset(&data, 0, sizeof(data));
	cl_git_pass(git_submodule_foreach(g_repo, sm_lookup_cb, &data));
	cl_assert_equal_i(8, data.count);
}