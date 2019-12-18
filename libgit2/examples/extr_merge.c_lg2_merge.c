#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char** annotated; int annotated_count; scalar_t__ heads; int /*<<< orphan*/  no_commit; } ;
typedef  TYPE_1__ merge_options ;
typedef  scalar_t__ git_repository_state_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int git_merge_preference_t ;
struct TYPE_13__ {int /*<<< orphan*/  file_flags; scalar_t__ flags; } ;
typedef  TYPE_2__ git_merge_options ;
typedef  int git_merge_analysis_t ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_14__ {int checkout_strategy; } ;
typedef  TYPE_3__ git_checkout_options ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int GIT_CHECKOUT_ALLOW_CONFLICTS ; 
 int GIT_CHECKOUT_FORCE ; 
 TYPE_3__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_MERGE_ANALYSIS_FASTFORWARD ; 
 int GIT_MERGE_ANALYSIS_NORMAL ; 
 int GIT_MERGE_ANALYSIS_UNBORN ; 
 int GIT_MERGE_ANALYSIS_UP_TO_DATE ; 
 int /*<<< orphan*/  GIT_MERGE_FILE_STYLE_DIFF3 ; 
 TYPE_2__ GIT_MERGE_OPTIONS_INIT ; 
 int GIT_MERGE_PREFERENCE_FASTFORWARD_ONLY ; 
 int GIT_MERGE_PREFERENCE_NO_FASTFORWARD ; 
 scalar_t__ GIT_REPOSITORY_STATE_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_lg2 (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_merge_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/ * git_annotated_commit_id (char*) ; 
 scalar_t__ git_index_has_conflicts (int /*<<< orphan*/ *) ; 
 int git_merge (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int,TYPE_2__*,TYPE_3__*) ; 
 int git_merge_analysis (int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int) ; 
 int git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ git_repository_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_options_init (TYPE_1__*) ; 
 int /*<<< orphan*/  output_conflicts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_options (char const**,TYPE_1__*,int,char**) ; 
 int perform_fastforward (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int resolve_heads (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

int lg2_merge(git_repository *repo, int argc, char **argv)
{
	merge_options opts;
	git_index *index;
	git_repository_state_t state;
	git_merge_analysis_t analysis;
	git_merge_preference_t preference;
	const char *path = ".";
	int err = 0;

	merge_options_init(&opts);
	parse_options(&path, &opts, argc, argv);

	state = git_repository_state(repo);
	if (state != GIT_REPOSITORY_STATE_NONE) {
		fprintf(stderr, "repository is in unexpected state %d\n", state);
		goto cleanup;
	}

	err = resolve_heads(repo, &opts);
	if (err != 0)
		goto cleanup;

	err = git_merge_analysis(&analysis, &preference,
	                         repo,
	                         (const git_annotated_commit **)opts.annotated,
	                         opts.annotated_count);
	check_lg2(err, "merge analysis failed", NULL);

	if (analysis & GIT_MERGE_ANALYSIS_UP_TO_DATE) {
		printf("Already up-to-date\n");
		return 0;
	} else if (analysis & GIT_MERGE_ANALYSIS_UNBORN ||
	          (analysis & GIT_MERGE_ANALYSIS_FASTFORWARD &&
	          !(preference & GIT_MERGE_PREFERENCE_NO_FASTFORWARD))) {
		const git_oid *target_oid;
		if (analysis & GIT_MERGE_ANALYSIS_UNBORN) {
			printf("Unborn\n");
		} else {
			printf("Fast-forward\n");
		}

		/* Since this is a fast-forward, there can be only one merge head */
		target_oid = git_annotated_commit_id(opts.annotated[0]);
		assert(opts.annotated_count == 1);

		return perform_fastforward(repo, target_oid, (analysis & GIT_MERGE_ANALYSIS_UNBORN));
	} else if (analysis & GIT_MERGE_ANALYSIS_NORMAL) {
		git_merge_options merge_opts = GIT_MERGE_OPTIONS_INIT;
		git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;

		merge_opts.flags = 0;
		merge_opts.file_flags = GIT_MERGE_FILE_STYLE_DIFF3;

		checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE|GIT_CHECKOUT_ALLOW_CONFLICTS;

		if (preference & GIT_MERGE_PREFERENCE_FASTFORWARD_ONLY) {
			printf("Fast-forward is preferred, but only a merge is possible\n");
			return -1;
		}

		err = git_merge(repo,
		                (const git_annotated_commit **)opts.annotated, opts.annotated_count,
		                &merge_opts, &checkout_opts);
		check_lg2(err, "merge failed", NULL);
	}

	/* If we get here, we actually performed the merge above */

	check_lg2(git_repository_index(&index, repo), "failed to get repository index", NULL);

	if (git_index_has_conflicts(index)) {
		/* Handle conflicts */
		output_conflicts(index);
	} else if (!opts.no_commit) {
		create_merge_commit(repo, index, &opts);
		printf("Merge made\n");
	}

cleanup:
	free((char **)opts.heads);
	free(opts.annotated);

	return 0;
}