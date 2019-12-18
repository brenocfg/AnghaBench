#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_18__ {int /*<<< orphan*/ * ptr; int /*<<< orphan*/  len; int /*<<< orphan*/  automergeable; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_merge_file_result ;
struct TYPE_19__ {int flags; scalar_t__ favor; } ;
typedef  TYPE_2__ git_merge_file_options ;
struct TYPE_20__ {TYPE_11__* theirs; TYPE_10__* ours; TYPE_9__* ancestor; int /*<<< orphan*/  repo; int /*<<< orphan*/  file_opts; } ;
typedef  TYPE_3__ git_merge_driver_source ;
struct TYPE_21__ {scalar_t__ favor; } ;
typedef  TYPE_4__ git_merge_driver__builtin ;
typedef  int /*<<< orphan*/  git_merge_driver ;
struct TYPE_22__ {char* ptr; int /*<<< orphan*/  asize; int /*<<< orphan*/  size; } ;
typedef  TYPE_5__ git_buf ;
struct TYPE_23__ {int /*<<< orphan*/  mode; int /*<<< orphan*/ * path; } ;
struct TYPE_17__ {int /*<<< orphan*/  mode; int /*<<< orphan*/ * path; } ;
struct TYPE_16__ {int /*<<< orphan*/  mode; int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 int GIT_EMERGECONFLICT ; 
 int GIT_MERGE_FILE_FAVOR__CONFLICTED ; 
 TYPE_2__ GIT_MERGE_FILE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int /*<<< orphan*/  git_merge_file__best_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* git_merge_file__best_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_merge_file_from_index (TYPE_1__*,int /*<<< orphan*/ ,TYPE_9__*,TYPE_10__*,TYPE_11__*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_merge_file_result_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int git_merge_driver__builtin_apply(
	git_merge_driver *self,
	const char **path_out,
	uint32_t *mode_out,
	git_buf *merged_out,
	const char *filter_name,
	const git_merge_driver_source *src)
{
	git_merge_driver__builtin *driver = (git_merge_driver__builtin *)self;
	git_merge_file_options file_opts = GIT_MERGE_FILE_OPTIONS_INIT;
	git_merge_file_result result = {0};
	int error;

	GIT_UNUSED(filter_name);

	if (src->file_opts)
		memcpy(&file_opts, src->file_opts, sizeof(git_merge_file_options));

	if (driver->favor)
		file_opts.favor = driver->favor;

	if ((error = git_merge_file_from_index(&result, src->repo,
		src->ancestor, src->ours, src->theirs, &file_opts)) < 0)
		goto done;

	if (!result.automergeable &&
		!(file_opts.flags & GIT_MERGE_FILE_FAVOR__CONFLICTED)) {
		error = GIT_EMERGECONFLICT;
		goto done;
	}

	*path_out = git_merge_file__best_path(
		src->ancestor ? src->ancestor->path : NULL,
		src->ours ? src->ours->path : NULL,
		src->theirs ? src->theirs->path : NULL);

	*mode_out = git_merge_file__best_mode(
		src->ancestor ? src->ancestor->mode : 0,
		src->ours ? src->ours->mode : 0,
		src->theirs ? src->theirs->mode : 0);

	merged_out->ptr = (char *)result.ptr;
	merged_out->size = result.len;
	merged_out->asize = result.len;
	result.ptr = NULL;

done:
	git_merge_file_result_free(&result);
	return error;
}