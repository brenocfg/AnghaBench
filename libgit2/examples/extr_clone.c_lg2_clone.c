#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {TYPE_1__ member_0; } ;
typedef  TYPE_4__ progress_data ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_16__ {int klass; char* message; } ;
typedef  TYPE_5__ git_error ;
struct TYPE_13__ {TYPE_4__* payload; int /*<<< orphan*/  credentials; int /*<<< orphan*/ * transfer_progress; int /*<<< orphan*/  sideband_progress; } ;
struct TYPE_14__ {TYPE_2__ callbacks; } ;
struct TYPE_18__ {TYPE_4__* progress_payload; int /*<<< orphan*/  progress_cb; int /*<<< orphan*/  checkout_strategy; } ;
struct TYPE_17__ {TYPE_3__ fetch_opts; TYPE_7__ checkout_opts; } ;
typedef  TYPE_6__ git_clone_options ;
typedef  TYPE_7__ git_checkout_options ;

/* Variables and functions */
 TYPE_7__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 TYPE_6__ GIT_CLONE_OPTIONS_INIT ; 
 int /*<<< orphan*/  checkout_progress ; 
 int /*<<< orphan*/  cred_acquire_cb ; 
 int /*<<< orphan*/  fetch_progress ; 
 int git_clone (int /*<<< orphan*/ **,char const*,char const*,TYPE_6__*) ; 
 TYPE_5__* git_error_last () ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sideband_progress ; 

int lg2_clone(git_repository *repo, int argc, char **argv)
{
	progress_data pd = {{0}};
	git_repository *cloned_repo = NULL;
	git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
	git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
	const char *url = argv[1];
	const char *path = argv[2];
	int error;

	(void)repo; /* unused */

	/* Validate args */
	if (argc < 3) {
		printf ("USAGE: %s <url> <path>\n", argv[0]);
		return -1;
	}

	/* Set up options */
	checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	checkout_opts.progress_cb = checkout_progress;
	checkout_opts.progress_payload = &pd;
	clone_opts.checkout_opts = checkout_opts;
	clone_opts.fetch_opts.callbacks.sideband_progress = sideband_progress;
	clone_opts.fetch_opts.callbacks.transfer_progress = &fetch_progress;
	clone_opts.fetch_opts.callbacks.credentials = cred_acquire_cb;
	clone_opts.fetch_opts.callbacks.payload = &pd;

	/* Do the clone */
	error = git_clone(&cloned_repo, url, path, &clone_opts);
	printf("\n");
	if (error != 0) {
		const git_error *err = git_error_last();
		if (err) printf("ERROR %d: %s\n", err->klass, err->message);
		else printf("ERROR %d: no detailed info\n", error);
	}
	else if (cloned_repo) git_repository_free(cloned_repo);
	return error;
}