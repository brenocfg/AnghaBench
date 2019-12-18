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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  _bgzf_file_t ;
struct TYPE_4__ {char open_mode; int block_length; int block_offset; scalar_t__ fp; int /*<<< orphan*/  block_address; int /*<<< orphan*/ * uncompressed_block; } ;
typedef  TYPE_1__ BGZF ;

/* Variables and functions */
 int /*<<< orphan*/  _bgzf_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bgzf_read_block (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

ssize_t bgzf_read(BGZF *fp, void *data, ssize_t length)
{
	ssize_t bytes_read = 0;
	uint8_t *output = data;
	if (length <= 0) return 0;
	assert(fp->open_mode == 'r');
	while (bytes_read < length) {
		int copy_length, available = fp->block_length - fp->block_offset;
		uint8_t *buffer;
		if (available <= 0) {
			if (bgzf_read_block(fp) != 0) return -1;
			available = fp->block_length - fp->block_offset;
			if (available <= 0) break;
		}
		copy_length = length - bytes_read < available? length - bytes_read : available;
		buffer = fp->uncompressed_block;
		memcpy(output, buffer + fp->block_offset, copy_length);
		fp->block_offset += copy_length;
		output += copy_length;
		bytes_read += copy_length;
	}
	if (fp->block_offset == fp->block_length) {
		fp->block_address = _bgzf_tell((_bgzf_file_t)fp->fp);
		fp->block_offset = fp->block_length = 0;
	}
	return bytes_read;
}