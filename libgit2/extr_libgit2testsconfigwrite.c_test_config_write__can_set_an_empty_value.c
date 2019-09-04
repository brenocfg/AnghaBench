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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_buf (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void test_config_write__can_set_an_empty_value(void)
{
	git_repository *repository;
	git_config *config;
	git_buf buf = {0};

	repository = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_repository_config(&config, repository));

	cl_git_pass(git_config_set_string(config, "core.somevar", ""));
	cl_git_pass(git_config_get_string_buf(&buf, config, "core.somevar"));
	cl_assert_equal_s("", buf.ptr);

	git_buf_dispose(&buf);
	git_config_free(config);
	cl_git_sandbox_cleanup();
}