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
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clean_test_config ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_buf (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 

void test_config_read__single_line(void)
{
	git_buf buf = GIT_BUF_INIT;
	git_config *cfg;

	cl_set_cleanup(&clean_test_config, NULL);
	cl_git_mkfile("./testconfig", "[some] var = value\n[some \"OtheR\"] var = value");
	cl_git_pass(git_config_open_ondisk(&cfg, "./testconfig"));
	cl_git_pass(git_config_get_string_buf(&buf, cfg, "some.var"));
	cl_assert_equal_s(buf.ptr, "value");

	git_buf_clear(&buf);
	cl_git_pass(git_config_get_string_buf(&buf, cfg, "some.OtheR.var"));
	cl_assert_equal_s(buf.ptr, "value");

	git_config_free(cfg);
	cl_git_mkfile("./testconfig", "[some] var = value\n[some \"OtheR\"]var = value");
	cl_git_pass(git_config_open_ondisk(&cfg, "./testconfig"));
	git_buf_clear(&buf);
	cl_git_pass(git_config_get_string_buf(&buf, cfg, "some.var"));
	cl_assert_equal_s(buf.ptr, "value");

	git_buf_clear(&buf);
	cl_git_pass(git_config_get_string_buf(&buf, cfg, "some.OtheR.var"));
	cl_assert_equal_s(buf.ptr, "value");

	git_config_free(cfg);
	git_buf_dispose(&buf);
}