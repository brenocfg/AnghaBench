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
struct TYPE_4__ {char open_mode; scalar_t__ block_offset; int block_address; int /*<<< orphan*/  errcode; int /*<<< orphan*/  fp; int /*<<< orphan*/  compressed_block; } ;
typedef  TYPE_1__ BGZF ;

/* Variables and functions */
 int /*<<< orphan*/  BGZF_ERR_IO ; 
 int /*<<< orphan*/  assert (int) ; 
 int deflate_block (TYPE_1__*,scalar_t__) ; 
 int fwrite (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int bgzf_flush(BGZF *fp)
{
	assert(fp->open_mode == 'w');
	while (fp->block_offset > 0) {
		int block_length;
		block_length = deflate_block(fp, fp->block_offset);
		if (block_length < 0) return -1;
		if (fwrite(fp->compressed_block, 1, block_length, fp->fp) != block_length) {
			fp->errcode |= BGZF_ERR_IO; // possibly truncated file
			return -1;
		}
		fp->block_address += block_length;
	}
	return 0;
}