#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct opts {scalar_t__ argc; } ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_STASH_DEFAULT ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* git_commit_summary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_default (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

__attribute__((used)) static int cmd_push(git_repository *repo, struct opts *opts)
{
	git_signature *signature;
	git_commit *stash;
	git_oid stashid;

	if (opts->argc)
		usage("push does not accept any parameters");

	check_lg2(git_signature_default(&signature, repo),
		  "Unable to get signature", NULL);
	check_lg2(git_stash_save(&stashid, repo, signature, NULL, GIT_STASH_DEFAULT),
		  "Unable to save stash", NULL);
	check_lg2(git_commit_lookup(&stash, repo, &stashid),
		  "Unable to lookup stash commit", NULL);

	printf("Saved working directory %s\n", git_commit_summary(stash));

	git_signature_free(signature);
	git_commit_free(stash);

	return 0;
}