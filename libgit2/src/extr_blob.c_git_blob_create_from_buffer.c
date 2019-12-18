#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_stream ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_odb_open_wstream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int git_odb_stream_finalize_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_stream_free (int /*<<< orphan*/ *) ; 
 int git_odb_stream_write (int /*<<< orphan*/ *,void const*,size_t) ; 
 int git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_blob_create_from_buffer(
	git_oid *id, git_repository *repo, const void *buffer, size_t len)
{
	int error;
	git_odb *odb;
	git_odb_stream *stream;

	assert(id && repo);

	if ((error = git_repository_odb__weakptr(&odb, repo)) < 0 ||
		(error = git_odb_open_wstream(&stream, odb, len, GIT_OBJECT_BLOB)) < 0)
		return error;

	if ((error = git_odb_stream_write(stream, buffer, len)) == 0)
		error = git_odb_stream_finalize_write(id, stream);

	git_odb_stream_free(stream);
	return error;
}