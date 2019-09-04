#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ tree_reader ;
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_reader ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  scalar_t__ git_off_t ;
typedef  int /*<<< orphan*/  git_filemode_t ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_BLOBSIZE (scalar_t__) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 scalar_t__ git_blob_rawsize (int /*<<< orphan*/ *) ; 
 int git_buf_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_tree_entry_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_tree_entry_filemode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_entry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_entry_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_owner (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tree_reader_read(
	git_buf *out,
	git_oid *out_id,
	git_filemode_t *out_filemode,
	git_reader *_reader,
	const char *filename)
{
	tree_reader *reader = (tree_reader *)_reader;
	git_tree_entry *tree_entry = NULL;
	git_blob *blob = NULL;
	git_off_t blobsize;
	int error;

	if ((error = git_tree_entry_bypath(&tree_entry, reader->tree, filename)) < 0 ||
	    (error = git_blob_lookup(&blob, git_tree_owner(reader->tree), git_tree_entry_id(tree_entry))) < 0)
		goto done;

	blobsize = git_blob_rawsize(blob);
	GIT_ERROR_CHECK_BLOBSIZE(blobsize);

	if ((error = git_buf_set(out, git_blob_rawcontent(blob), (size_t)blobsize)) < 0)
		goto done;

	if (out_id)
		git_oid_cpy(out_id, git_tree_entry_id(tree_entry));

	if (out_filemode)
		*out_filemode = git_tree_entry_filemode(tree_entry);

done:
	git_blob_free(blob);
	git_tree_entry_free(tree_entry);
	return error;
}