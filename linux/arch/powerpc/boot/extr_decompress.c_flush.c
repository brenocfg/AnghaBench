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
 unsigned long decompressed_bytes ; 
 unsigned long limit ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 char* output_buffer ; 
 unsigned long skip ; 

__attribute__((used)) static long flush(void *v, unsigned long buffer_size)
{
	unsigned long end = decompressed_bytes + buffer_size;
	unsigned long size = buffer_size;
	unsigned long offset = 0;
	char *in = v;
	char *out;

	/*
	 * if we hit our decompression limit, we need to fake an error to abort
	 * the in-progress decompression.
	 */
	if (decompressed_bytes >= limit)
		return -1;

	/* skip this entire block */
	if (end <= skip) {
		decompressed_bytes += buffer_size;
		return buffer_size;
	}

	/* skip some data at the start, but keep the rest of the block */
	if (decompressed_bytes < skip && end > skip) {
		offset = skip - decompressed_bytes;

		in += offset;
		size -= offset;
		decompressed_bytes += offset;
	}

	out = &output_buffer[decompressed_bytes - skip];
	size = min(decompressed_bytes + size, limit) - decompressed_bytes;

	memcpy(out, in, size);
	decompressed_bytes += size;

	return buffer_size;
}