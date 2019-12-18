#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_11__ {scalar_t__ src; size_t idx; int /*<<< orphan*/  blob; TYPE_4__* file; int /*<<< orphan*/  repo; int /*<<< orphan*/ * odb_obj; TYPE_9__ data; } ;
typedef  TYPE_2__ similarity_info ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_12__ {TYPE_1__* metric; } ;
typedef  TYPE_3__ git_diff_find_options ;
struct TYPE_13__ {scalar_t__ size; int /*<<< orphan*/  id; int /*<<< orphan*/  path; } ;
typedef  TYPE_4__ git_diff_file ;
struct TYPE_10__ {int (* file_signature ) (void**,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* buffer_signature ) (void**,TYPE_4__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 scalar_t__ GIT_ITERATOR_TYPE_WORKDIR ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 scalar_t__ git__is_sizet (scalar_t__) ; 
 int git_blob_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ ) ; 
 scalar_t__ git_blob_rawsize (int /*<<< orphan*/ ) ; 
 int git_buf_joinpath (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_object__from_odb_object (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int stub1 (void**,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (void**,TYPE_4__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int similarity_sig(
	similarity_info *info,
	const git_diff_find_options *opts,
	void **cache)
{
	int error = 0;
	git_diff_file *file = info->file;

	if (info->src == GIT_ITERATOR_TYPE_WORKDIR) {
		if ((error = git_buf_joinpath(
			&info->data, git_repository_workdir(info->repo), file->path)) < 0)
			return error;

		/* if path is not a regular file, just skip this item */
		if (!git_path_isfile(info->data.ptr))
			return 0;

		/* TODO: apply wd-to-odb filters to file data if necessary */

		error = opts->metric->file_signature(
			&cache[info->idx], info->file,
			info->data.ptr, opts->metric->payload);
	} else {
		/* if we didn't initially know the size, we might have an odb_obj
		 * around from earlier, so convert that, otherwise load the blob now
		 */
		if (info->odb_obj != NULL)
			error = git_object__from_odb_object(
				(git_object **)&info->blob, info->repo,
				info->odb_obj, GIT_OBJECT_BLOB);
		else
			error = git_blob_lookup(&info->blob, info->repo, &file->id);

		if (error < 0) {
			/* if lookup fails, just skip this item in similarity calc */
			git_error_clear();
		} else {
			size_t sz;

			/* index size may not be actual blob size if filtered */
			if (file->size != git_blob_rawsize(info->blob))
				file->size = git_blob_rawsize(info->blob);

			sz = (size_t)(git__is_sizet(file->size) ? file->size : -1);

			error = opts->metric->buffer_signature(
				&cache[info->idx], info->file,
				git_blob_rawcontent(info->blob), sz, opts->metric->payload);
		}
	}

	return error;
}