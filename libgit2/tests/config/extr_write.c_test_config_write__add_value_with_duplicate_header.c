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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char const*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char const*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string (char const**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  git_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void test_config_write__add_value_with_duplicate_header(void)
{
	const char *file_name  = "config-duplicate-insert";
	const char *entry_name = "foo.c";
	const char *old_val    = "old";
	const char *new_val    = "new";
	const char *str;
	git_config *cfg, *snapshot;

	/* c = old should be replaced by c = new.
	 * The bug causes c = new to be inserted under the first 'foo' header.
	 */
	const char *file_content =
		"[foo]\n"   \
		"  a = b\n" \
		"[other]\n" \
		"  a = b\n" \
		"[foo]\n"   \
		"  c = old\n";

	/* Write the test config */
	cl_git_mkfile(file_name, file_content);
	cl_git_pass(git_config_open_ondisk(&cfg, file_name));

	/* make sure the expected entry (foo.c) exists */
	cl_git_pass(git_config_snapshot(&snapshot, cfg));
	cl_git_pass(git_config_get_string(&str, snapshot, entry_name));
	cl_assert_equal_s(old_val, str);
	git_config_free(snapshot);

	/* Try setting foo.c to something else */
	cl_git_pass(git_config_set_string(cfg, entry_name, new_val));
	git_config_free(cfg);

	/* Reopen the file and make sure the new value was set */
	cl_git_pass(git_config_open_ondisk(&cfg, file_name));
	cl_git_pass(git_config_snapshot(&snapshot, cfg));
	cl_git_pass(git_config_get_string(&str, snapshot, entry_name));
	cl_assert_equal_s(new_val, str);

	/* Cleanup */
	git_config_free(snapshot);
	git_config_free(cfg);
}