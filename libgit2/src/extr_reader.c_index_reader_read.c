#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  repo; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ index_reader ;
typedef  int /*<<< orphan*/  git_reader ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_filemode_t ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int git_blob__getbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* git_index_get_bypath (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int index_reader_read(
	git_buf *out,
	git_oid *out_id,
	git_filemode_t *out_filemode,
	git_reader *_reader,
	const char *filename)
{
	index_reader *reader = (index_reader *)_reader;
	const git_index_entry *entry;
	git_blob *blob;
	int error;

	if ((entry = git_index_get_bypath(reader->index, filename, 0)) == NULL)
		return GIT_ENOTFOUND;

	if ((error = git_blob_lookup(&blob, reader->repo, &entry->id)) < 0)
		goto done;

	if (out_id)
		git_oid_cpy(out_id, &entry->id);

	if (out_filemode)
		*out_filemode = entry->mode;

	error = git_blob__getbuf(out, blob);

done:
	git_blob_free(blob);
	return error;
}