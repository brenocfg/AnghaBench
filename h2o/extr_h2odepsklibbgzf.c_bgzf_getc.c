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
typedef  int /*<<< orphan*/  _bgzf_file_t ;
struct TYPE_4__ {scalar_t__ block_offset; scalar_t__ block_length; scalar_t__ fp; int /*<<< orphan*/  block_address; scalar_t__ uncompressed_block; } ;
typedef  TYPE_1__ BGZF ;

/* Variables and functions */
 int /*<<< orphan*/  _bgzf_tell (int /*<<< orphan*/ ) ; 
 scalar_t__ bgzf_read_block (TYPE_1__*) ; 

int bgzf_getc(BGZF *fp)
{
	int c;
	if (fp->block_offset >= fp->block_length) {
		if (bgzf_read_block(fp) != 0) return -2; /* error */
		if (fp->block_length == 0) return -1; /* end-of-file */
	}
	c = ((unsigned char*)fp->uncompressed_block)[fp->block_offset++];
    if (fp->block_offset == fp->block_length) {
        fp->block_address = _bgzf_tell((_bgzf_file_t)fp->fp);
        fp->block_offset = 0;
        fp->block_length = 0;
    }
	return c;
}