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
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,char const*) ; 

void test_config_write__repeated(void)
{
	const char *filename = "config-repeated";
	git_config *cfg;
	git_buf result = GIT_BUF_INIT;
	const char *expected = "[sample \"prefix\"]\n\
\tsetting1 = someValue1\n\
\tsetting2 = someValue2\n\
\tsetting3 = someValue3\n\
\tsetting4 = someValue4\n\
";
	cl_git_pass(git_config_open_ondisk(&cfg, filename));
	cl_git_pass(git_config_set_string(cfg, "sample.prefix.setting1", "someValue1"));
	cl_git_pass(git_config_set_string(cfg, "sample.prefix.setting2", "someValue2"));
	cl_git_pass(git_config_set_string(cfg, "sample.prefix.setting3", "someValue3"));
	cl_git_pass(git_config_set_string(cfg, "sample.prefix.setting4", "someValue4"));
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, filename));

	cl_git_pass(git_futils_readbuffer(&result, filename));
	cl_assert_equal_s(expected, result.ptr);
	git_buf_dispose(&result);

	git_config_free(cfg);
}