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
struct repository {int dummy; } ;
struct replay_opts {scalar_t__ no_commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  advise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  git_path_cherry_pick_head (struct repository*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_advice(struct repository *r, int show_hint,
			 struct replay_opts *opts)
{
	char *msg = getenv("GIT_CHERRY_PICK_HELP");

	if (msg) {
		fprintf(stderr, "%s\n", msg);
		/*
		 * A conflict has occurred but the porcelain
		 * (typically rebase --interactive) wants to take care
		 * of the commit itself so remove CHERRY_PICK_HEAD
		 */
		unlink(git_path_cherry_pick_head(r));
		return;
	}

	if (show_hint) {
		if (opts->no_commit)
			advise(_("after resolving the conflicts, mark the corrected paths\n"
				 "with 'git add <paths>' or 'git rm <paths>'"));
		else
			advise(_("after resolving the conflicts, mark the corrected paths\n"
				 "with 'git add <paths>' or 'git rm <paths>'\n"
				 "and commit the result with 'git commit'"));
	}
}