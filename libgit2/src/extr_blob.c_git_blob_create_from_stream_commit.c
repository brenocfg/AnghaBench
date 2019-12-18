#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_writestream ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int /*<<< orphan*/  path_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  hintpath; TYPE_2__ fbuf; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ blob_writestream ;

/* Variables and functions */
 int /*<<< orphan*/  blob_writestream_free (int /*<<< orphan*/ *) ; 
 int git_blob__create_from_paths (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int git_filebuf_flush (TYPE_2__*) ; 

int git_blob_create_from_stream_commit(git_oid *out, git_writestream *_stream)
{
	int error;
	blob_writestream *stream = (blob_writestream *) _stream;

	/*
	 * We can make this more officient by avoiding writing to
	 * disk, but for now let's re-use the helper functions we
	 * have.
	 */
	if ((error = git_filebuf_flush(&stream->fbuf)) < 0)
		goto cleanup;

	error = git_blob__create_from_paths(out, NULL, stream->repo, stream->fbuf.path_lock,
					    stream->hintpath, 0, !!stream->hintpath);

cleanup:
	blob_writestream_free(_stream);
	return error;

}