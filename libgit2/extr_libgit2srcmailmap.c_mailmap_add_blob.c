#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_mailmap ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_blob__getbuf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int mailmap_add_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mailmap_add_blob(
	git_mailmap *mm, git_repository *repo, const char *rev)
{
	git_object *object = NULL;
	git_blob *blob = NULL;
	git_buf content = GIT_BUF_INIT;
	int error;

	assert(mm && repo);

	error = git_revparse_single(&object, repo, rev);
	if (error < 0)
		goto cleanup;

	error = git_object_peel((git_object **)&blob, object, GIT_OBJECT_BLOB);
	if (error < 0)
		goto cleanup;

	error = git_blob__getbuf(&content, blob);
	if (error < 0)
		goto cleanup;

	error = mailmap_add_buffer(mm, content.ptr, content.size);
	if (error < 0)
		goto cleanup;

cleanup:
	git_buf_dispose(&content);
	git_blob_free(blob);
	git_object_free(object);
	return error;
}