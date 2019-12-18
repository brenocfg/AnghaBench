#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_3__ {char open_mode; int block_address; int block_offset; scalar_t__ block_length; int /*<<< orphan*/  errcode; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ BGZF ;

/* Variables and functions */
 int /*<<< orphan*/  BGZF_ERR_IO ; 
 int /*<<< orphan*/  BGZF_ERR_MISUSE ; 
 int SEEK_SET ; 
 scalar_t__ _bgzf_seek (int /*<<< orphan*/ ,int,int) ; 

int64_t bgzf_seek(BGZF* fp, int64_t pos, int where)
{
	int block_offset;
	int64_t block_address;

	if (fp->open_mode != 'r' || where != SEEK_SET) {
		fp->errcode |= BGZF_ERR_MISUSE;
		return -1;
	}
	block_offset = pos & 0xFFFF;
	block_address = pos >> 16;
	if (_bgzf_seek(fp->fp, block_address, SEEK_SET) < 0) {
		fp->errcode |= BGZF_ERR_IO;
		return -1;
	}
	fp->block_length = 0;  // indicates current block has not been loaded
	fp->block_address = block_address;
	fp->block_offset = block_offset;
	return 0;
}