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
struct notify_data {char* file; char* sha; } ;
struct TYPE_4__ {int checkout_strategy; struct notify_data* notify_payload; int /*<<< orphan*/  notify_cb; int /*<<< orphan*/  notify_flags; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int GIT_CHECKOUT_ALLOW_CONFLICTS ; 
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_CONFLICT ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  test_checkout_notify_cb ; 

void test_checkout_index__can_notify_of_skipped_files(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	struct notify_data data;

	cl_git_mkfile("./testrepo/new.txt", "This isn't what's stored!");

	/*
	 * $ git ls-tree HEAD
	 * 100644 blob a8233120f6ad708f843d861ce2b7228ec4e3dec6    README
	 * 100644 blob 3697d64be941a53d4ae8f6a271e4e3fa56b022cc    branch_file.txt
	 * 100644 blob a71586c1dfe8a71c6cbf6c129f404c5642ff31bd    new.txt
	 */
	data.file = "new.txt";
	data.sha = "a71586c1dfe8a71c6cbf6c129f404c5642ff31bd";

	opts.checkout_strategy = GIT_CHECKOUT_SAFE |
		GIT_CHECKOUT_RECREATE_MISSING |
		GIT_CHECKOUT_ALLOW_CONFLICTS;
	opts.notify_flags = GIT_CHECKOUT_NOTIFY_CONFLICT;
	opts.notify_cb = test_checkout_notify_cb;
	opts.notify_payload = &data;

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));
}