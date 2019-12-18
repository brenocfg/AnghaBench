#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reader ;
typedef  int /*<<< orphan*/  git_indexwriter ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_1__ git_apply_options ;
typedef  int git_apply_location_t ;

/* Variables and functions */
 int GIT_APPLY_CHECK ; 
#define  GIT_APPLY_LOCATION_BOTH 130 
#define  GIT_APPLY_LOCATION_INDEX 129 
#define  GIT_APPLY_LOCATION_WORKDIR 128 
 TYPE_1__ GIT_APPLY_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_APPLY_OPTIONS_VERSION ; 
 int GIT_EINVALID ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_1__ const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_INDEXWRITER_INIT ; 
 int apply_deltas (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_apply__to_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int git_apply__to_workdir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int git_index_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_indexwriter_cleanup (int /*<<< orphan*/ *) ; 
 int git_indexwriter_commit (int /*<<< orphan*/ *) ; 
 int git_indexwriter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_reader_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_reader_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_reader_free (int /*<<< orphan*/ *) ; 
 int git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

int git_apply(
	git_repository *repo,
	git_diff *diff,
	git_apply_location_t location,
	const git_apply_options *given_opts)
{
	git_indexwriter indexwriter = GIT_INDEXWRITER_INIT;
	git_index *index = NULL, *preimage = NULL, *postimage = NULL;
	git_reader *pre_reader = NULL, *post_reader = NULL;
	git_apply_options opts = GIT_APPLY_OPTIONS_INIT;
	int error = GIT_EINVALID;

	assert(repo && diff);

	GIT_ERROR_CHECK_VERSION(
		given_opts, GIT_APPLY_OPTIONS_VERSION, "git_apply_options");

	if (given_opts)
		memcpy(&opts, given_opts, sizeof(git_apply_options));

	/*
	 * by default, we apply a patch directly to the working directory;
	 * in `--cached` or `--index` mode, we apply to the contents already
	 * in the index.
	 */
	switch (location) {
	case GIT_APPLY_LOCATION_BOTH:
		error = git_reader_for_workdir(&pre_reader, repo, true);
		break;
	case GIT_APPLY_LOCATION_INDEX:
		error = git_reader_for_index(&pre_reader, repo, NULL);
		break;
	case GIT_APPLY_LOCATION_WORKDIR:
		error = git_reader_for_workdir(&pre_reader, repo, false);
		break;
	default:
		assert(false);
	}

	if (error < 0)
		goto done;

	/*
	 * Build the preimage and postimage (differences).  Note that
	 * this is not the complete preimage or postimage, it only
	 * contains the files affected by the patch.  We want to avoid
	 * having the full repo index, so we will limit our checkout
	 * to only write these files that were affected by the diff.
	 */
	if ((error = git_index_new(&preimage)) < 0 ||
	    (error = git_index_new(&postimage)) < 0 ||
	    (error = git_reader_for_index(&post_reader, repo, postimage)) < 0)
		goto done;

	if (!(opts.flags & GIT_APPLY_CHECK))
		if ((error = git_repository_index(&index, repo)) < 0 ||
		    (error = git_indexwriter_init(&indexwriter, index)) < 0)
			goto done;

	if ((error = apply_deltas(repo, pre_reader, preimage, post_reader, postimage, diff, &opts)) < 0)
		goto done;

	if ((opts.flags & GIT_APPLY_CHECK))
		goto done;

	switch (location) {
	case GIT_APPLY_LOCATION_BOTH:
		error = git_apply__to_workdir(repo, diff, preimage, postimage, location, &opts);
		break;
	case GIT_APPLY_LOCATION_INDEX:
		error = git_apply__to_index(repo, diff, preimage, postimage, &opts);
		break;
	case GIT_APPLY_LOCATION_WORKDIR:
		error = git_apply__to_workdir(repo, diff, preimage, postimage, location, &opts);
		break;
	default:
		assert(false);
	}

	if (error < 0)
		goto done;

	error = git_indexwriter_commit(&indexwriter);

done:
	git_indexwriter_cleanup(&indexwriter);
	git_index_free(postimage);
	git_index_free(preimage);
	git_index_free(index);
	git_reader_free(pre_reader);
	git_reader_free(post_reader);

	return error;
}