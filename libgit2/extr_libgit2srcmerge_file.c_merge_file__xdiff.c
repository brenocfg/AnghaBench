#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  flags; } ;
struct TYPE_24__ {int automergeable; char const* ptr; int /*<<< orphan*/  mode; int /*<<< orphan*/  len; int /*<<< orphan*/ * path; int /*<<< orphan*/  marker_size; TYPE_1__ xpp; int /*<<< orphan*/  style; int /*<<< orphan*/  level; int /*<<< orphan*/  favor; int /*<<< orphan*/ * file2; int /*<<< orphan*/ * file1; int /*<<< orphan*/ * ancestor; } ;
typedef  TYPE_2__ xmparam_t ;
struct TYPE_25__ {char* ptr; int /*<<< orphan*/  size; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ mmfile_t ;
struct TYPE_26__ {int /*<<< orphan*/  size; scalar_t__ ptr; } ;
typedef  TYPE_4__ mmbuffer_t ;
typedef  TYPE_2__ git_merge_file_result ;
struct TYPE_27__ {scalar_t__ favor; int flags; int /*<<< orphan*/  marker_size; int /*<<< orphan*/ * their_label; int /*<<< orphan*/ * our_label; int /*<<< orphan*/ * ancestor_label; } ;
typedef  TYPE_6__ git_merge_file_options ;
struct TYPE_28__ {int /*<<< orphan*/  mode; int /*<<< orphan*/ * path; int /*<<< orphan*/  size; scalar_t__ ptr; } ;
typedef  TYPE_7__ git_merge_file_input ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_MERGE ; 
 int GIT_MERGE_FILE_DIFF_MINIMAL ; 
 int GIT_MERGE_FILE_DIFF_PATIENCE ; 
 scalar_t__ GIT_MERGE_FILE_FAVOR_OURS ; 
 scalar_t__ GIT_MERGE_FILE_FAVOR_THEIRS ; 
 scalar_t__ GIT_MERGE_FILE_FAVOR_UNION ; 
 int GIT_MERGE_FILE_IGNORE_WHITESPACE ; 
 int GIT_MERGE_FILE_IGNORE_WHITESPACE_CHANGE ; 
 int GIT_MERGE_FILE_IGNORE_WHITESPACE_EOL ; 
 TYPE_6__ GIT_MERGE_FILE_OPTIONS_INIT ; 
 int GIT_MERGE_FILE_SIMPLIFY_ALNUM ; 
 int GIT_MERGE_FILE_STYLE_DIFF3 ; 
 int /*<<< orphan*/  XDF_IGNORE_WHITESPACE ; 
 int /*<<< orphan*/  XDF_IGNORE_WHITESPACE_AT_EOL ; 
 int /*<<< orphan*/  XDF_IGNORE_WHITESPACE_CHANGE ; 
 int /*<<< orphan*/  XDF_NEED_MINIMAL ; 
 int /*<<< orphan*/  XDF_PATIENCE_DIFF ; 
 int /*<<< orphan*/  XDL_MERGE_DIFF3 ; 
 int /*<<< orphan*/  XDL_MERGE_FAVOR_OURS ; 
 int /*<<< orphan*/  XDL_MERGE_FAVOR_THEIRS ; 
 int /*<<< orphan*/  XDL_MERGE_FAVOR_UNION ; 
 int /*<<< orphan*/  XDL_MERGE_ZEALOUS ; 
 int /*<<< orphan*/  XDL_MERGE_ZEALOUS_ALNUM ; 
 int /*<<< orphan*/ * git__strdup (char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_merge_file__best_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* git_merge_file__best_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_merge_file_result_free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  merge_file_normalize_opts (TYPE_6__*,TYPE_6__ const*) ; 
 int xdl_merge (TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_2__*,TYPE_4__*) ; 

__attribute__((used)) static int merge_file__xdiff(
	git_merge_file_result *out,
	const git_merge_file_input *ancestor,
	const git_merge_file_input *ours,
	const git_merge_file_input *theirs,
	const git_merge_file_options *given_opts)
{
	xmparam_t xmparam;
	mmfile_t ancestor_mmfile = {0}, our_mmfile = {0}, their_mmfile = {0};
	mmbuffer_t mmbuffer;
	git_merge_file_options options = GIT_MERGE_FILE_OPTIONS_INIT;
	const char *path;
	int xdl_result;
	int error = 0;

	memset(out, 0x0, sizeof(git_merge_file_result));

	merge_file_normalize_opts(&options, given_opts);

	memset(&xmparam, 0x0, sizeof(xmparam_t));

	if (ancestor) {
		xmparam.ancestor = (options.ancestor_label) ?
			options.ancestor_label : ancestor->path;
		ancestor_mmfile.ptr = (char *)ancestor->ptr;
		ancestor_mmfile.size = ancestor->size;
	}

	xmparam.file1 = (options.our_label) ?
		options.our_label : ours->path;
	our_mmfile.ptr = (char *)ours->ptr;
	our_mmfile.size = ours->size;

	xmparam.file2 = (options.their_label) ?
		options.their_label : theirs->path;
	their_mmfile.ptr = (char *)theirs->ptr;
	their_mmfile.size = theirs->size;

	if (options.favor == GIT_MERGE_FILE_FAVOR_OURS)
		xmparam.favor = XDL_MERGE_FAVOR_OURS;
	else if (options.favor == GIT_MERGE_FILE_FAVOR_THEIRS)
		xmparam.favor = XDL_MERGE_FAVOR_THEIRS;
	else if (options.favor == GIT_MERGE_FILE_FAVOR_UNION)
		xmparam.favor = XDL_MERGE_FAVOR_UNION;

	xmparam.level = (options.flags & GIT_MERGE_FILE_SIMPLIFY_ALNUM) ?
		XDL_MERGE_ZEALOUS_ALNUM : XDL_MERGE_ZEALOUS;

	if (options.flags & GIT_MERGE_FILE_STYLE_DIFF3)
		xmparam.style = XDL_MERGE_DIFF3;

	if (options.flags & GIT_MERGE_FILE_IGNORE_WHITESPACE)
		xmparam.xpp.flags |= XDF_IGNORE_WHITESPACE;
	if (options.flags & GIT_MERGE_FILE_IGNORE_WHITESPACE_CHANGE)
		xmparam.xpp.flags |= XDF_IGNORE_WHITESPACE_CHANGE;
	if (options.flags & GIT_MERGE_FILE_IGNORE_WHITESPACE_EOL)
		xmparam.xpp.flags |= XDF_IGNORE_WHITESPACE_AT_EOL;

	if (options.flags & GIT_MERGE_FILE_DIFF_PATIENCE)
		xmparam.xpp.flags |= XDF_PATIENCE_DIFF;

	if (options.flags & GIT_MERGE_FILE_DIFF_MINIMAL)
		xmparam.xpp.flags |= XDF_NEED_MINIMAL;

	xmparam.marker_size = options.marker_size;

	if ((xdl_result = xdl_merge(&ancestor_mmfile, &our_mmfile,
		&their_mmfile, &xmparam, &mmbuffer)) < 0) {
		git_error_set(GIT_ERROR_MERGE, "failed to merge files");
		error = -1;
		goto done;
	}

	path = git_merge_file__best_path(
		ancestor ? ancestor->path : NULL,
		ours->path,
		theirs->path);

	if (path != NULL && (out->path = git__strdup(path)) == NULL) {
		error = -1;
		goto done;
	}

	out->automergeable = (xdl_result == 0);
	out->ptr = (const char *)mmbuffer.ptr;
	out->len = mmbuffer.size;
	out->mode = git_merge_file__best_mode(
		ancestor ? ancestor->mode : 0,
		ours->mode,
		theirs->mode);

done:
	if (error < 0)
		git_merge_file_result_free(out);

	return error;
}