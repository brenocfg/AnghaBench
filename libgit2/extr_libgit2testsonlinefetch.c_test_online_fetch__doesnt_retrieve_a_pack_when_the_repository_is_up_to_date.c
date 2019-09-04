#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_10__ {int* payload; int /*<<< orphan*/ * transfer_progress; } ;
struct TYPE_8__ {int /*<<< orphan*/  download_tags; TYPE_3__ callbacks; } ;
typedef  TYPE_1__ git_fetch_options ;
struct TYPE_9__ {int bare; } ;
typedef  TYPE_2__ git_clone_options ;

/* Variables and functions */
 TYPE_2__ GIT_CLONE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 TYPE_1__ GIT_FETCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,char*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_remote_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_download (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_remote_update_tips (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  transferProgressCallback ; 

void test_online_fetch__doesnt_retrieve_a_pack_when_the_repository_is_up_to_date(void)
{
	git_repository *_repository;
	bool invoked = false;
	git_remote *remote;
	git_fetch_options options = GIT_FETCH_OPTIONS_INIT;
	git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
	opts.bare = true;

	cl_git_pass(git_clone(&_repository, "https://github.com/libgit2/TestGitRepository.git",
				"./fetch/lg2", &opts));
	git_repository_free(_repository);

	cl_git_pass(git_repository_open(&_repository, "./fetch/lg2"));

	cl_git_pass(git_remote_lookup(&remote, _repository, "origin"));
	cl_git_pass(git_remote_connect(remote, GIT_DIRECTION_FETCH, NULL, NULL, NULL));

	cl_assert_equal_i(false, invoked);

	options.callbacks.transfer_progress = &transferProgressCallback;
	options.callbacks.payload = &invoked;
	cl_git_pass(git_remote_download(remote, NULL, &options));

	cl_assert_equal_i(false, invoked);

	cl_git_pass(git_remote_update_tips(remote, &options.callbacks, 1, options.download_tags, NULL));
	git_remote_disconnect(remote);

	git_remote_free(remote);
	git_repository_free(_repository);
}