#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_remote_autotag_option_t ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_5__ {size_t* payload; int /*<<< orphan*/  update_tips; int /*<<< orphan*/  transfer_progress; } ;
struct TYPE_6__ {int /*<<< orphan*/  download_tags; TYPE_1__ callbacks; } ;
typedef  TYPE_2__ git_fetch_options ;

/* Variables and functions */
 TYPE_2__ GIT_FETCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (scalar_t__,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ counter ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  progress ; 
 int /*<<< orphan*/  update_tips ; 

__attribute__((used)) static void do_fetch(const char *url, git_remote_autotag_option_t flag, int n)
{
	git_remote *remote;
	git_fetch_options options = GIT_FETCH_OPTIONS_INIT;
	size_t bytes_received = 0;

	options.callbacks.transfer_progress = progress;
	options.callbacks.update_tips = update_tips;
	options.callbacks.payload = &bytes_received;
	options.download_tags = flag;
	counter = 0;

	cl_git_pass(git_remote_create(&remote, _repo, "test", url));
	cl_git_pass(git_remote_fetch(remote, NULL, &options, NULL));
	cl_assert_equal_i(counter, n);
	cl_assert(bytes_received > 0);

	git_remote_free(remote);
}