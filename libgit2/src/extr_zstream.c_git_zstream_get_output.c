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
struct TYPE_4__ {scalar_t__ in_len; scalar_t__ zerr; scalar_t__ flush; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_ZLIB ; 
 scalar_t__ Z_FINISH ; 
 scalar_t__ Z_STREAM_END ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_zstream_get_output_chunk (void*,size_t*,TYPE_1__*) ; 

int git_zstream_get_output(void *out, size_t *out_len, git_zstream *zstream)
{
	size_t out_remain = *out_len;

	if (zstream->in_len && zstream->zerr == Z_STREAM_END) {
		git_error_set(GIT_ERROR_ZLIB, "zlib input had trailing garbage");
		return -1;
	}

	while (out_remain > 0 && zstream->zerr != Z_STREAM_END) {
		size_t out_written = out_remain;

		if (git_zstream_get_output_chunk(out, &out_written, zstream) < 0)
			return -1;

		out_remain -= out_written;
		out = ((char *)out) + out_written;
	}

	/* either we finished the input or we did not flush the data */
	assert(zstream->in_len > 0 || zstream->flush == Z_FINISH);

	/* set out_size to number of bytes actually written to output */
	*out_len = *out_len - out_remain;

	return 0;
}