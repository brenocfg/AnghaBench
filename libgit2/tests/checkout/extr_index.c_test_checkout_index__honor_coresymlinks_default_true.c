#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int GIT_PATH_MAX ; 
 int /*<<< orphan*/  check_file_contents (char*,char*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  create_tmp_global_config (char*,char*,char*) ; 
 int /*<<< orphan*/  git_path_supports_symlinks (char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int p_readlink (char*,char*,int) ; 
 int /*<<< orphan*/  populate_symlink_workdir () ; 
 int /*<<< orphan*/  strlen (char*) ; 

void test_checkout_index__honor_coresymlinks_default_true(void)
{
	char link_data[GIT_PATH_MAX];
	int link_size = GIT_PATH_MAX;

	cl_must_pass(p_mkdir("symlink", 0777));

	if (!git_path_supports_symlinks("symlink/test"))
		cl_skip();

#ifdef GIT_WIN32
	/*
	 * Windows explicitly requires the global configuration to have
	 * core.symlinks=true in addition to actual filesystem support.
	 */
	create_tmp_global_config("tmp_global_path", "core.symlinks", "true");
#endif

	populate_symlink_workdir();

	link_size = p_readlink("./symlink/link_to_new.txt", link_data, link_size);
	cl_assert(link_size >= 0);

	link_data[link_size] = '\0';
	cl_assert_equal_i(link_size, strlen("new.txt"));
	cl_assert_equal_s(link_data, "new.txt");
	check_file_contents("./symlink/link_to_new.txt", "my new file\n");
}