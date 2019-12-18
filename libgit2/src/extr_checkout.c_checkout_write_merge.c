#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;

/* Type definitions */
struct TYPE_33__ {scalar_t__ mode; int /*<<< orphan*/  len; scalar_t__ ptr; int /*<<< orphan*/ * path; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ git_merge_file_result ;
struct TYPE_34__ {char* ancestor_label; char* our_label; char* their_label; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ git_merge_file_options ;
struct TYPE_35__ {int /*<<< orphan*/ * temp_buf; int /*<<< orphan*/ * attr_session; } ;
typedef  TYPE_4__ git_filter_options ;
typedef  int /*<<< orphan*/  git_filter_list ;
typedef  int /*<<< orphan*/  git_filebuf ;
struct TYPE_36__ {char* ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_5__ git_buf ;
struct TYPE_32__ {int checkout_strategy; char* ancestor_label; char* our_label; char* their_label; int /*<<< orphan*/  dir_mode; int /*<<< orphan*/  disable_filters; } ;
struct TYPE_37__ {int strategy; TYPE_1__ opts; int /*<<< orphan*/  repo; int /*<<< orphan*/  tmp; int /*<<< orphan*/  attr_session; } ;
typedef  TYPE_6__ checkout_data ;
struct TYPE_38__ {TYPE_12__* theirs; TYPE_11__* ours; int /*<<< orphan*/  ancestor; } ;
typedef  TYPE_7__ checkout_conflictdata ;
struct TYPE_31__ {int /*<<< orphan*/  path; } ;
struct TYPE_30__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 TYPE_5__ GIT_BUF_INIT ; 
 int GIT_CHECKOUT_CONFLICT_STYLE_DIFF3 ; 
 int GIT_CHECKOUT_UPDATE_ONLY ; 
 int GIT_ECONFLICT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECKOUT ; 
 int /*<<< orphan*/  GIT_FILEBUF_DO_NOT_BUFFER ; 
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 TYPE_4__ GIT_FILTER_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_FILTER_TO_WORKTREE ; 
 TYPE_3__ GIT_MERGE_FILE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_MERGE_FILE_STYLE_DIFF3 ; 
 int checkout_merge_path (TYPE_5__*,TYPE_6__*,TYPE_7__*,TYPE_2__*) ; 
 int checkout_safe_for_update_only (TYPE_6__*,void*,scalar_t__) ; 
 int conflict_entry_name (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 void* git_buf_cstr (TYPE_5__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_5__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int git_filebuf_open (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int git_filebuf_write (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int git_filter_list__load_ext (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int git_filter_list_apply_to_data (TYPE_5__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  git_filter_list_free (int /*<<< orphan*/ *) ; 
 int git_merge_file_from_index (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*,TYPE_12__*,TYPE_3__*) ; 
 int /*<<< orphan*/  git_merge_file_result_free (TYPE_2__*) ; 
 int mkpath2file (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_write_merge(
	checkout_data *data,
	checkout_conflictdata *conflict)
{
	git_buf our_label = GIT_BUF_INIT, their_label = GIT_BUF_INIT,
		path_suffixed = GIT_BUF_INIT, path_workdir = GIT_BUF_INIT,
		in_data = GIT_BUF_INIT, out_data = GIT_BUF_INIT;
	git_merge_file_options opts = GIT_MERGE_FILE_OPTIONS_INIT;
	git_merge_file_result result = {0};
	git_filebuf output = GIT_FILEBUF_INIT;
	git_filter_list *fl = NULL;
	git_filter_options filter_opts = GIT_FILTER_OPTIONS_INIT;
	int error = 0;

	if (data->opts.checkout_strategy & GIT_CHECKOUT_CONFLICT_STYLE_DIFF3)
		opts.flags |= GIT_MERGE_FILE_STYLE_DIFF3;

	opts.ancestor_label = data->opts.ancestor_label ?
		data->opts.ancestor_label : "ancestor";
	opts.our_label = data->opts.our_label ?
		data->opts.our_label : "ours";
	opts.their_label = data->opts.their_label ?
		data->opts.their_label : "theirs";

	/* If all the paths are identical, decorate the diff3 file with the branch
	 * names.  Otherwise, append branch_name:path.
	 */
	if (conflict->ours && conflict->theirs &&
		strcmp(conflict->ours->path, conflict->theirs->path) != 0) {

		if ((error = conflict_entry_name(
			&our_label, opts.our_label, conflict->ours->path)) < 0 ||
			(error = conflict_entry_name(
			&their_label, opts.their_label, conflict->theirs->path)) < 0)
			goto done;

		opts.our_label = git_buf_cstr(&our_label);
		opts.their_label = git_buf_cstr(&their_label);
	}

	if ((error = git_merge_file_from_index(&result, data->repo,
		conflict->ancestor, conflict->ours, conflict->theirs, &opts)) < 0)
		goto done;

	if (result.path == NULL || result.mode == 0) {
		git_error_set(GIT_ERROR_CHECKOUT, "could not merge contents of file");
		error = GIT_ECONFLICT;
		goto done;
	}

	if ((error = checkout_merge_path(&path_workdir, data, conflict, &result)) < 0)
		goto done;

	if ((data->strategy & GIT_CHECKOUT_UPDATE_ONLY) != 0 &&
		(error = checkout_safe_for_update_only(data, git_buf_cstr(&path_workdir), result.mode)) <= 0)
		goto done;

	if (!data->opts.disable_filters) {
		in_data.ptr = (char *)result.ptr;
		in_data.size = result.len;

		filter_opts.attr_session = &data->attr_session;
		filter_opts.temp_buf = &data->tmp;

		if ((error = git_filter_list__load_ext(
				&fl, data->repo, NULL, git_buf_cstr(&path_workdir),
				GIT_FILTER_TO_WORKTREE, &filter_opts)) < 0 ||
			(error = git_filter_list_apply_to_data(&out_data, fl, &in_data)) < 0)
			goto done;
	} else {
		out_data.ptr = (char *)result.ptr;
		out_data.size = result.len;
	}

	if ((error = mkpath2file(data, path_workdir.ptr, data->opts.dir_mode)) < 0 ||
		(error = git_filebuf_open(&output, git_buf_cstr(&path_workdir), GIT_FILEBUF_DO_NOT_BUFFER, result.mode)) < 0 ||
		(error = git_filebuf_write(&output, out_data.ptr, out_data.size)) < 0 ||
		(error = git_filebuf_commit(&output)) < 0)
		goto done;

done:
	git_filter_list_free(fl);

	git_buf_dispose(&out_data);
	git_buf_dispose(&our_label);
	git_buf_dispose(&their_label);

	git_merge_file_result_free(&result);
	git_buf_dispose(&path_workdir);
	git_buf_dispose(&path_suffixed);

	return error;
}