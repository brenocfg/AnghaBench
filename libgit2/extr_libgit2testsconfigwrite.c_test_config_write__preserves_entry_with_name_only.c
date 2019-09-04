#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,char const*) ; 

void test_config_write__preserves_entry_with_name_only(void)
{
	const char *file_name  = "config-empty-value";
	git_config *cfg;
	git_buf newfile = GIT_BUF_INIT;

	/* Write the test config and make sure the expected entry exists */
	cl_git_mkfile(file_name, "[section \"foo\"]\n\tname\n");
	cl_git_pass(git_config_open_ondisk(&cfg, file_name));
	cl_git_pass(git_config_set_string(cfg, "newsection.newname", "new_value"));
	cl_git_pass(git_config_set_string(cfg, "section.foo.other", "otherval"));

	cl_git_pass(git_futils_readbuffer(&newfile, file_name));
	cl_assert_equal_s("[section \"foo\"]\n\tname\n\tother = otherval\n[newsection]\n\tnewname = new_value\n", newfile.ptr);

	git_buf_dispose(&newfile);
	git_config_free(cfg);
}