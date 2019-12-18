#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ size; } ;
struct TYPE_12__ {TYPE_2__* delta; TYPE_1__ hunks; } ;
typedef  TYPE_3__ git_patch ;
struct TYPE_13__ {int mode; int /*<<< orphan*/  path; } ;
typedef  TYPE_4__ git_diff_file ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_apply_options ;
struct TYPE_14__ {int /*<<< orphan*/  opts; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ apply_hunks_ctx ;
struct TYPE_11__ {scalar_t__ status; int flags; TYPE_4__ new_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_APPLY_OPTIONS_INIT ; 
 scalar_t__ GIT_DELTA_DELETED ; 
 int GIT_DIFF_FLAG_BINARY ; 
 unsigned int GIT_FILEMODE_BLOB ; 
 int apply_binary (int /*<<< orphan*/ *,char const*,size_t,TYPE_3__*) ; 
 int apply_err (char*) ; 
 int apply_hunks (int /*<<< orphan*/ *,char const*,size_t,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_len (int /*<<< orphan*/ *) ; 
 int git_buf_put (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int git_apply__patch(
	git_buf *contents_out,
	char **filename_out,
	unsigned int *mode_out,
	const char *source,
	size_t source_len,
	git_patch *patch,
	const git_apply_options *given_opts)
{
	apply_hunks_ctx ctx = { GIT_APPLY_OPTIONS_INIT };
	char *filename = NULL;
	unsigned int mode = 0;
	int error = 0;

	assert(contents_out && filename_out && mode_out && (source || !source_len) && patch);

	if (given_opts)
		memcpy(&ctx.opts, given_opts, sizeof(git_apply_options));

	*filename_out = NULL;
	*mode_out = 0;

	if (patch->delta->status != GIT_DELTA_DELETED) {
		const git_diff_file *newfile = &patch->delta->new_file;

		filename = git__strdup(newfile->path);
		mode = newfile->mode ?
			newfile->mode : GIT_FILEMODE_BLOB;
	}

	if (patch->delta->flags & GIT_DIFF_FLAG_BINARY)
		error = apply_binary(contents_out, source, source_len, patch);
	else if (patch->hunks.size)
		error = apply_hunks(contents_out, source, source_len, patch, &ctx);
	else
		error = git_buf_put(contents_out, source, source_len);

	if (error)
		goto done;

	if (patch->delta->status == GIT_DELTA_DELETED &&
		git_buf_len(contents_out) > 0) {
		error = apply_err("removal patch leaves file contents");
		goto done;
	}

	*filename_out = filename;
	*mode_out = mode;

done:
	if (error < 0)
		git__free(filename);

	return error;
}