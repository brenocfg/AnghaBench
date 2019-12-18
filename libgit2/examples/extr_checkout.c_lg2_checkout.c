#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct args_info {size_t pos; size_t argc; char** argv; } ;
typedef  scalar_t__ git_repository_state_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_annotated_commit ;
typedef  int /*<<< orphan*/  checkout_options ;
struct TYPE_2__ {char* message; } ;

/* Variables and functions */
 struct args_info ARGS_INFO_INIT ; 
 scalar_t__ GIT_REPOSITORY_STATE_NONE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_error_last () ; 
 scalar_t__ git_repository_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_options (char const**,int /*<<< orphan*/ *,struct args_info*) ; 
 int perform_checkout_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int resolve_refish (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int lg2_checkout(git_repository *repo, int argc, char **argv)
{
	struct args_info args = ARGS_INFO_INIT;
	checkout_options opts;
	git_repository_state_t state;
	git_annotated_commit *checkout_target = NULL;
	int err = 0;
	const char *path = ".";

	/** Parse our command line options */
	parse_options(&path, &opts, &args);

	/** Make sure we're not about to checkout while something else is going on */
	state = git_repository_state(repo);
	if (state != GIT_REPOSITORY_STATE_NONE) {
		fprintf(stderr, "repository is in unexpected state %d\n", state);
		goto cleanup;
	}

	if (args.pos >= args.argc) {
		fprintf(stderr, "unhandled\n");
		err = -1;
		goto cleanup;
	} else if (!strcmp("--", args.argv[args.pos])) {
		/**
		 * Try to checkout the given path
		 */

		fprintf(stderr, "unhandled path-based checkout\n");
		err = 1;
		goto cleanup;
	} else {
		/**
		 * Try to resolve a "refish" argument to a target libgit2 can use
		 */
		err = resolve_refish(&checkout_target, repo, args.argv[args.pos]);
		if (err != 0) {
			fprintf(stderr, "failed to resolve %s: %s\n", args.argv[args.pos], git_error_last()->message);
			goto cleanup;
		}
		err = perform_checkout_ref(repo, checkout_target, &opts);
	}

cleanup:
	git_annotated_commit_free(checkout_target);

	return err;
}