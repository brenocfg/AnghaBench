#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ git_off_t ;
typedef  int /*<<< orphan*/  git_odb_stream ;
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/ * free; int /*<<< orphan*/ * finalize_write; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; int /*<<< orphan*/ * backend; } ;
struct TYPE_7__ {size_t size; TYPE_1__ stream; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ fake_wstream ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_BLOBSIZE (scalar_t__) ; 
 int /*<<< orphan*/  GIT_STREAM_WRONLY ; 
 int /*<<< orphan*/  fake_wstream__free ; 
 int /*<<< orphan*/  fake_wstream__fwrite ; 
 int /*<<< orphan*/  fake_wstream__write ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int /*<<< orphan*/ * git__malloc (size_t) ; 

__attribute__((used)) static int init_fake_wstream(git_odb_stream **stream_p, git_odb_backend *backend, git_off_t size, git_object_t type)
{
	fake_wstream *stream;
	size_t blobsize;

	GIT_ERROR_CHECK_BLOBSIZE(size);
	blobsize = (size_t)size;

	stream = git__calloc(1, sizeof(fake_wstream));
	GIT_ERROR_CHECK_ALLOC(stream);

	stream->size = blobsize;
	stream->type = type;
	stream->buffer = git__malloc(blobsize);
	if (stream->buffer == NULL) {
		git__free(stream);
		return -1;
	}

	stream->stream.backend = backend;
	stream->stream.read = NULL; /* read only */
	stream->stream.write = &fake_wstream__write;
	stream->stream.finalize_write = &fake_wstream__fwrite;
	stream->stream.free = &fake_wstream__free;
	stream->stream.mode = GIT_STREAM_WRONLY;

	*stream_p = (git_odb_stream *)stream;
	return 0;
}