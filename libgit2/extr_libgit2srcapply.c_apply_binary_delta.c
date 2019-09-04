#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ inflatedlen; scalar_t__ type; int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ git_diff_binary_file ;
struct TYPE_12__ {scalar_t__ size; size_t asize; void* ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 scalar_t__ GIT_DIFF_BINARY_DELTA ; 
 scalar_t__ GIT_DIFF_BINARY_LITERAL ; 
 int apply_err (char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_put (TYPE_2__*,char const*,size_t) ; 
 int /*<<< orphan*/  git_buf_swap (TYPE_2__*,TYPE_2__*) ; 
 int git_delta_apply (void**,size_t*,void*,size_t,void*,scalar_t__) ; 
 int git_zstream_inflatebuf (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_binary_delta(
	git_buf *out,
	const char *source,
	size_t source_len,
	git_diff_binary_file *binary_file)
{
	git_buf inflated = GIT_BUF_INIT;
	int error = 0;

	/* no diff means identical contents */
	if (binary_file->datalen == 0)
		return git_buf_put(out, source, source_len);

	error = git_zstream_inflatebuf(&inflated,
		binary_file->data, binary_file->datalen);

	if (!error && inflated.size != binary_file->inflatedlen) {
		error = apply_err("inflated delta does not match expected length");
		git_buf_dispose(out);
	}

	if (error < 0)
		goto done;

	if (binary_file->type == GIT_DIFF_BINARY_DELTA) {
		void *data;
		size_t data_len;

		error = git_delta_apply(&data, &data_len, (void *)source, source_len,
			(void *)inflated.ptr, inflated.size);

		out->ptr = data;
		out->size = data_len;
		out->asize = data_len;
	}
	else if (binary_file->type == GIT_DIFF_BINARY_LITERAL) {
		git_buf_swap(out, &inflated);
	}
	else {
		error = apply_err("unknown binary delta type");
		goto done;
	}

done:
	git_buf_dispose(&inflated);
	return error;
}