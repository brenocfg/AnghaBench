#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_zstream_t ;
typedef  int /*<<< orphan*/  git_zstream ;
struct TYPE_4__ {size_t asize; size_t size; char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ZSTREAM_INIT ; 
 int git_buf_grow_by (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  git_zstream_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_zstream_free (int /*<<< orphan*/ *) ; 
 int git_zstream_get_output (char*,size_t*,int /*<<< orphan*/ *) ; 
 int git_zstream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_zstream_set_input (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t git_zstream_suggest_output_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zstream_buf(git_buf *out, const void *in, size_t in_len, git_zstream_t type)
{
	git_zstream zs = GIT_ZSTREAM_INIT;
	int error = 0;

	if ((error = git_zstream_init(&zs, type)) < 0)
		return error;

	if ((error = git_zstream_set_input(&zs, in, in_len)) < 0)
		goto done;

	while (!git_zstream_done(&zs)) {
		size_t step = git_zstream_suggest_output_len(&zs), written;

		if ((error = git_buf_grow_by(out, step)) < 0)
			goto done;

		written = out->asize - out->size;

		if ((error = git_zstream_get_output(
				out->ptr + out->size, &written, &zs)) < 0)
			goto done;

		out->size += written;
	}

	/* NULL terminate for consistency if possible */
	if (out->size < out->asize)
		out->ptr[out->size] = '\0';

done:
	git_zstream_free(&zs);
	return error;
}