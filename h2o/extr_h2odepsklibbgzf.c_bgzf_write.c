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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ssize_t ;
struct TYPE_4__ {char open_mode; int block_offset; int /*<<< orphan*/ * uncompressed_block; } ;
typedef  TYPE_1__ BGZF ;

/* Variables and functions */
 int BGZF_BLOCK_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bgzf_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

ssize_t bgzf_write(BGZF *fp, const void *data, ssize_t length)
{
	const uint8_t *input = data;
	int block_length = BGZF_BLOCK_SIZE, bytes_written;
	assert(fp->open_mode == 'w');
	input = data;
	bytes_written = 0;
	while (bytes_written < length) {
		uint8_t* buffer = fp->uncompressed_block;
		int copy_length = block_length - fp->block_offset < length - bytes_written? block_length - fp->block_offset : length - bytes_written;
		memcpy(buffer + fp->block_offset, input, copy_length);
		fp->block_offset += copy_length;
		input += copy_length;
		bytes_written += copy_length;
		if (fp->block_offset == block_length && bgzf_flush(fp)) break;
	}
	return bytes_written;
}