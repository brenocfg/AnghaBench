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
struct option {int dummy; } ;
struct notes_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTES_INIT_WRITABLE ; 
 int NOTES_PRUNE_DRYRUN ; 
 int NOTES_PRUNE_VERBOSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_END () ; 
 struct option OPT__DRY_RUN (int*,int /*<<< orphan*/ ) ; 
 struct option OPT__VERBOSE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  commit_notes (int /*<<< orphan*/ ,struct notes_tree*,char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_notes (struct notes_tree*) ; 
 int /*<<< orphan*/  git_notes_prune_usage ; 
 struct notes_tree* init_notes_check (char*,int /*<<< orphan*/ ) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prune_notes (struct notes_tree*,int) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

__attribute__((used)) static int prune(int argc, const char **argv, const char *prefix)
{
	struct notes_tree *t;
	int show_only = 0, verbose = 0;
	struct option options[] = {
		OPT__DRY_RUN(&show_only, N_("do not remove, show only")),
		OPT__VERBOSE(&verbose, N_("report pruned notes")),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options, git_notes_prune_usage,
			     0);

	if (argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_prune_usage, options);
	}

	t = init_notes_check("prune", NOTES_INIT_WRITABLE);

	prune_notes(t, (verbose ? NOTES_PRUNE_VERBOSE : 0) |
		(show_only ? NOTES_PRUNE_VERBOSE|NOTES_PRUNE_DRYRUN : 0) );
	if (!show_only)
		commit_notes(the_repository, t,
			     "Notes removed by 'git notes prune'");
	free_notes(t);
	return 0;
}