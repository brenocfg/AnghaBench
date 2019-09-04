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
struct TYPE_4__ {int checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  check_file_contents (char*,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

void test_checkout_index__honor_the_gitattributes_directives(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	const char *attributes =
		"branch_file.txt text eol=crlf\n"
		"new.txt text eol=lf\n";

	cl_git_mkfile("./testrepo/.gitattributes", attributes);
	cl_repo_set_bool(g_repo, "core.autocrlf", false);

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_RECREATE_MISSING;

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	check_file_contents("./testrepo/README", "hey there\n");
	check_file_contents("./testrepo/new.txt", "my new file\n");
	check_file_contents("./testrepo/branch_file.txt", "hi\r\nbye!\r\n");
}