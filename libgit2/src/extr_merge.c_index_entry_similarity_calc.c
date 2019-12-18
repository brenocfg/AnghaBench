#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  scalar_t__ git_off_t ;
struct TYPE_13__ {TYPE_3__* metric; } ;
typedef  TYPE_4__ git_merge_options ;
struct TYPE_14__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  file_size; int /*<<< orphan*/  path; int /*<<< orphan*/  id; } ;
typedef  TYPE_5__ git_index_entry ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {TYPE_2__ member_0; } ;
struct TYPE_15__ {scalar_t__ flags; int /*<<< orphan*/  mode; int /*<<< orphan*/  size; int /*<<< orphan*/  path; int /*<<< orphan*/  id; TYPE_1__ member_0; } ;
typedef  TYPE_6__ git_diff_file ;
typedef  int /*<<< orphan*/  git_blob ;
struct TYPE_12__ {int (* buffer_signature ) (void**,TYPE_6__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  git__is_sizet (scalar_t__) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 scalar_t__ git_blob_rawsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (void**,TYPE_6__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int index_entry_similarity_calc(
	void **out,
	git_repository *repo,
	git_index_entry *entry,
	const git_merge_options *opts)
{
	git_blob *blob;
	git_diff_file diff_file = {{{0}}};
	git_off_t blobsize;
	int error;

	*out = NULL;

	if ((error = git_blob_lookup(&blob, repo, &entry->id)) < 0)
		return error;

	git_oid_cpy(&diff_file.id, &entry->id);
	diff_file.path = entry->path;
	diff_file.size = entry->file_size;
	diff_file.mode = entry->mode;
	diff_file.flags = 0;

	blobsize = git_blob_rawsize(blob);

	/* file too big for rename processing */
	if (!git__is_sizet(blobsize))
		return 0;

	error = opts->metric->buffer_signature(out, &diff_file,
		git_blob_rawcontent(blob), (size_t)blobsize,
		opts->metric->payload);

	git_blob_free(blob);

	return error;
}