#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  size_t git_off_t ;
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_filter_source ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__is_sizet (size_t) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 size_t git_blob_rawsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 char* git_filter_source_path (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_filter_source_repo (int /*<<< orphan*/  const*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * memchr (void const*,char,size_t) ; 

__attribute__((used)) static int has_cr_in_index(const git_filter_source *src)
{
	git_repository *repo = git_filter_source_repo(src);
	const char *path = git_filter_source_path(src);
	git_index *index;
	const git_index_entry *entry;
	git_blob *blob;
	const void *blobcontent;
	git_off_t blobsize;
	bool found_cr;

	if (!path)
		return false;

	if (git_repository_index__weakptr(&index, repo) < 0) {
		git_error_clear();
		return false;
	}

	if (!(entry = git_index_get_bypath(index, path, 0)) &&
		!(entry = git_index_get_bypath(index, path, 1)))
		return false;

	if (!S_ISREG(entry->mode)) /* don't crlf filter non-blobs */
		return true;

	if (git_blob_lookup(&blob, repo, &entry->id) < 0)
		return false;

	blobcontent = git_blob_rawcontent(blob);
	blobsize    = git_blob_rawsize(blob);
	if (!git__is_sizet(blobsize))
		blobsize = (size_t)-1;

	found_cr = (blobcontent != NULL &&
		blobsize > 0 &&
		memchr(blobcontent, '\r', (size_t)blobsize) != NULL);

	git_blob_free(blob);
	return found_cr;
}