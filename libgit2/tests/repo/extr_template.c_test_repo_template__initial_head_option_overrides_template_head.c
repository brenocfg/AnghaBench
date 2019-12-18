#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; char* initial_head; } ;
typedef  TYPE_1__ git_repository_init_options ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE ; 
 int GIT_REPOSITORY_INIT_MKPATH ; 
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  setup_repo (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  setup_templates (char*,int) ; 

void test_repo_template__initial_head_option_overrides_template_head(void)
{
	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;
	git_buf head = GIT_BUF_INIT;

	opts.flags = GIT_REPOSITORY_INIT_MKPATH | GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE;
	opts.initial_head = "manual";

	setup_templates("template", true);
	cl_git_mkfile("template/HEAD", "foobar\n");
	setup_repo("repo", &opts);

	cl_git_pass(git_futils_readbuffer(&head, "repo/.git/HEAD"));
	cl_assert_equal_s("ref: refs/heads/manual\n", head.ptr);

	git_buf_dispose(&head);
}