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
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ sm_lookup_data ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_delete_entry (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_submodule_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sm_lookup_cb ; 

void test_submodule_lookup__foreach(void)
{
	git_config *cfg;
	sm_lookup_data data;

	memset(&data, 0, sizeof(data));
	cl_git_pass(git_submodule_foreach(g_repo, sm_lookup_cb, &data));
	cl_assert_equal_i(8, data.count);

	memset(&data, 0, sizeof(data));

	/* Change the path for a submodule so it doesn't match the name */
	cl_git_pass(git_config_open_ondisk(&cfg, "submod2/.gitmodules"));

	cl_git_pass(git_config_set_string(cfg, "submodule.smchangedindex.path", "sm_changed_index"));
	cl_git_pass(git_config_set_string(cfg, "submodule.smchangedindex.url", "../submod2_target"));
	cl_git_pass(git_config_delete_entry(cfg, "submodule.sm_changed_index.path"));
	cl_git_pass(git_config_delete_entry(cfg, "submodule.sm_changed_index.url"));

	git_config_free(cfg);

	cl_git_pass(git_submodule_foreach(g_repo, sm_lookup_cb, &data));
	cl_assert_equal_i(8, data.count);
}