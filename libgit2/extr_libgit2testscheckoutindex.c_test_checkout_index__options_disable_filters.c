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
struct TYPE_4__ {int checkout_strategy; int disable_filters; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  check_file_contents (char*,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_checkout_index__options_disable_filters(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	cl_git_mkfile("./testrepo/.gitattributes", "*.txt text eol=crlf\n");

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_RECREATE_MISSING;
	opts.disable_filters = false;

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	check_file_contents("./testrepo/new.txt", "my new file\r\n");

	p_unlink("./testrepo/new.txt");

	opts.disable_filters = true;
	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	check_file_contents("./testrepo/new.txt", "my new file\n");
}