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
struct TYPE_4__ {char* template_path; } ;
typedef  TYPE_1__ git_repository_init_options ;

/* Variables and functions */
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_repository (char*) ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init_ext (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 

void test_repo_init__empty_template_path(void)
{
	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;
	opts.template_path = "";

	cl_git_pass(git_futils_mkdir("foo", 0755, 0));
	cl_git_pass(git_repository_init_ext(&_repo, "foo", &opts));

	cleanup_repository("foo");
}