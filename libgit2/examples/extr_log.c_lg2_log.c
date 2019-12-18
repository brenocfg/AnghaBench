#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct log_state {int /*<<< orphan*/  walker; int /*<<< orphan*/ * repo; int /*<<< orphan*/  revisions; } ;
struct log_options {int min_parents; int max_parents; int limit; scalar_t__ show_diff; int /*<<< orphan*/  skip; int /*<<< orphan*/  grep; int /*<<< orphan*/  committer; int /*<<< orphan*/  author; } ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_pathspec ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_7__ {char** strings; int count; } ;
struct TYPE_6__ {TYPE_3__ pathspec; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_FORMAT_PATCH ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_PATHSPEC_NO_MATCH_ERROR ; 
 int /*<<< orphan*/  add_revision (struct log_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_output ; 
 int /*<<< orphan*/  git_commit_author (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_committer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_parent (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_commit_parentcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_pathspec_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_pathspec_match_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pathspec_new (int /*<<< orphan*/ **,TYPE_3__*) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_message_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ match_with_parent (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int parse_options (struct log_state*,struct log_options*,int,char**) ; 
 int /*<<< orphan*/  print_commit (int /*<<< orphan*/ *,struct log_options*) ; 
 int /*<<< orphan*/  signature_matches (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lg2_log(git_repository *repo, int argc, char *argv[])
{
	int i, count = 0, printed = 0, parents, last_arg;
	struct log_state s;
	struct log_options opt;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	git_oid oid;
	git_commit *commit = NULL;
	git_pathspec *ps = NULL;

	/** Parse arguments and set up revwalker. */
	last_arg = parse_options(&s, &opt, argc, argv);
	s.repo = repo;

	diffopts.pathspec.strings = &argv[last_arg];
	diffopts.pathspec.count	  = argc - last_arg;
	if (diffopts.pathspec.count > 0)
		check_lg2(git_pathspec_new(&ps, &diffopts.pathspec),
			"Building pathspec", NULL);

	if (!s.revisions)
		add_revision(&s, NULL);

	/** Use the revwalker to traverse the history. */

	printed = count = 0;

	for (; !git_revwalk_next(&oid, s.walker); git_commit_free(commit)) {
		check_lg2(git_commit_lookup(&commit, s.repo, &oid),
			"Failed to look up commit", NULL);

		parents = (int)git_commit_parentcount(commit);
		if (parents < opt.min_parents)
			continue;
		if (opt.max_parents > 0 && parents > opt.max_parents)
			continue;

		if (diffopts.pathspec.count > 0) {
			int unmatched = parents;

			if (parents == 0) {
				git_tree *tree;
				check_lg2(git_commit_tree(&tree, commit), "Get tree", NULL);
				if (git_pathspec_match_tree(
						NULL, tree, GIT_PATHSPEC_NO_MATCH_ERROR, ps) != 0)
					unmatched = 1;
				git_tree_free(tree);
			} else if (parents == 1) {
				unmatched = match_with_parent(commit, 0, &diffopts) ? 0 : 1;
			} else {
				for (i = 0; i < parents; ++i) {
					if (match_with_parent(commit, i, &diffopts))
						unmatched--;
				}
			}

			if (unmatched > 0)
				continue;
		}

		if (!signature_matches(git_commit_author(commit), opt.author))
			continue;

		if (!signature_matches(git_commit_committer(commit), opt.committer))
			continue;

		if (!log_message_matches(commit, opt.grep))
			continue;

		if (count++ < opt.skip)
			continue;
		if (opt.limit != -1 && printed++ >= opt.limit) {
			git_commit_free(commit);
			break;
		}

		print_commit(commit, &opt);

		if (opt.show_diff) {
			git_tree *a = NULL, *b = NULL;
			git_diff *diff = NULL;

			if (parents > 1)
				continue;
			check_lg2(git_commit_tree(&b, commit), "Get tree", NULL);
			if (parents == 1) {
				git_commit *parent;
				check_lg2(git_commit_parent(&parent, commit, 0), "Get parent", NULL);
				check_lg2(git_commit_tree(&a, parent), "Tree for parent", NULL);
				git_commit_free(parent);
			}

			check_lg2(git_diff_tree_to_tree(
				&diff, git_commit_owner(commit), a, b, &diffopts),
				"Diff commit with parent", NULL);
			check_lg2(
                git_diff_print(diff, GIT_DIFF_FORMAT_PATCH, diff_output, NULL),
				"Displaying diff", NULL);

			git_diff_free(diff);
			git_tree_free(a);
			git_tree_free(b);
		}
	}

	git_pathspec_free(ps);
	git_revwalk_free(s.walker);

	return 0;
}