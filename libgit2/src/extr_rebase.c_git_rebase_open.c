#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_rebase_options ;
struct TYPE_16__ {int type; int head_detached; int /*<<< orphan*/  orig_head_name; int /*<<< orphan*/  onto_id; int /*<<< orphan*/  orig_head_id; int /*<<< orphan*/  state_path; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ git_rebase ;
struct TYPE_17__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_REBASE ; 
#define  GIT_REBASE_TYPE_APPLY 130 
#define  GIT_REBASE_TYPE_INTERACTIVE 129 
#define  GIT_REBASE_TYPE_MERGE 128 
 int GIT_REBASE_TYPE_NONE ; 
 int /*<<< orphan*/  HEAD_FILE ; 
 int /*<<< orphan*/  HEAD_NAME_FILE ; 
 int /*<<< orphan*/  ONTO_FILE ; 
 int /*<<< orphan*/  ORIG_DETACHED_HEAD ; 
 int /*<<< orphan*/  ORIG_HEAD_FILE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_detach (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t git_buf_len (TYPE_2__*) ; 
 int git_buf_puts (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_futils_readbuffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_rebase_free (TYPE_1__*) ; 
 scalar_t__ rebase_alloc (TYPE_1__**,int /*<<< orphan*/  const*) ; 
 int rebase_check_versions (int /*<<< orphan*/  const*) ; 
 int rebase_open_merge (TYPE_1__*) ; 
 int rebase_state_type (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_rebase_open(
	git_rebase **out,
	git_repository *repo,
	const git_rebase_options *given_opts)
{
	git_rebase *rebase;
	git_buf path = GIT_BUF_INIT, orig_head_name = GIT_BUF_INIT,
		orig_head_id = GIT_BUF_INIT, onto_id = GIT_BUF_INIT;
	size_t state_path_len;
	int error;

	assert(repo);

	if ((error = rebase_check_versions(given_opts)) < 0)
		return error;

	if (rebase_alloc(&rebase, given_opts) < 0)
		return -1;

	rebase->repo = repo;

	if ((error = rebase_state_type(&rebase->type, &rebase->state_path, repo)) < 0)
		goto done;

	if (rebase->type == GIT_REBASE_TYPE_NONE) {
		git_error_set(GIT_ERROR_REBASE, "there is no rebase in progress");
		error = GIT_ENOTFOUND;
		goto done;
	}

	if ((error = git_buf_puts(&path, rebase->state_path)) < 0)
		goto done;

	state_path_len = git_buf_len(&path);

	if ((error = git_buf_joinpath(&path, path.ptr, HEAD_NAME_FILE)) < 0 ||
		(error = git_futils_readbuffer(&orig_head_name, path.ptr)) < 0)
		goto done;

	git_buf_rtrim(&orig_head_name);

	if (strcmp(ORIG_DETACHED_HEAD, orig_head_name.ptr) == 0)
		rebase->head_detached = 1;

	git_buf_truncate(&path, state_path_len);

	if ((error = git_buf_joinpath(&path, path.ptr, ORIG_HEAD_FILE)) < 0)
		goto done;

	if (!git_path_isfile(path.ptr)) {
		/* Previous versions of git.git used 'head' here; support that. */
		git_buf_truncate(&path, state_path_len);

		if ((error = git_buf_joinpath(&path, path.ptr, HEAD_FILE)) < 0)
			goto done;
	}

	if ((error = git_futils_readbuffer(&orig_head_id, path.ptr)) < 0)
		goto done;

	git_buf_rtrim(&orig_head_id);

	if ((error = git_oid_fromstr(&rebase->orig_head_id, orig_head_id.ptr)) < 0)
		goto done;

	git_buf_truncate(&path, state_path_len);

	if ((error = git_buf_joinpath(&path, path.ptr, ONTO_FILE)) < 0 ||
		(error = git_futils_readbuffer(&onto_id, path.ptr)) < 0)
		goto done;

	git_buf_rtrim(&onto_id);

	if ((error = git_oid_fromstr(&rebase->onto_id, onto_id.ptr)) < 0)
		goto done;

	if (!rebase->head_detached)
		rebase->orig_head_name = git_buf_detach(&orig_head_name);

	switch (rebase->type) {
	case GIT_REBASE_TYPE_INTERACTIVE:
		git_error_set(GIT_ERROR_REBASE, "interactive rebase is not supported");
		error = -1;
		break;
	case GIT_REBASE_TYPE_MERGE:
		error = rebase_open_merge(rebase);
		break;
	case GIT_REBASE_TYPE_APPLY:
		git_error_set(GIT_ERROR_REBASE, "patch application rebase is not supported");
		error = -1;
		break;
	default:
		abort();
	}

done:
	if (error == 0)
		*out = rebase;
	else
		git_rebase_free(rebase);

	git_buf_dispose(&path);
	git_buf_dispose(&orig_head_name);
	git_buf_dispose(&orig_head_id);
	git_buf_dispose(&onto_id);
	return error;
}