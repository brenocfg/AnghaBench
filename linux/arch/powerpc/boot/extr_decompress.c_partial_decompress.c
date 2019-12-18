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

/* Variables and functions */
 int __decompress (void*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long decompressed_bytes ; 
 int /*<<< orphan*/  flush ; 
 long limit ; 
 void* output_buffer ; 
 int /*<<< orphan*/  print_err ; 
 long skip ; 

long partial_decompress(void *inbuf, unsigned long input_size,
	void *outbuf, unsigned long output_size, unsigned long _skip)
{
	int ret;

	/*
	 * The skipped bytes needs to be included in the size of data we want
	 * to decompress.
	 */
	output_size += _skip;

	decompressed_bytes = 0;
	output_buffer = outbuf;
	limit = output_size;
	skip = _skip;

	ret = __decompress(inbuf, input_size, NULL, flush, outbuf,
		output_size, NULL, print_err);

	/*
	 * If decompression was aborted due to an actual error rather than
	 * a fake error that we used to abort, then we should report it.
	 */
	if (decompressed_bytes < limit)
		return ret;

	return decompressed_bytes - skip;
}