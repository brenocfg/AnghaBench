#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char open_mode; struct TYPE_8__* compressed_block; struct TYPE_8__* uncompressed_block; int /*<<< orphan*/  fp; int /*<<< orphan*/  errcode; } ;
typedef  TYPE_1__ BGZF ;

/* Variables and functions */
 int /*<<< orphan*/  BGZF_ERR_IO ; 
 int _bgzf_close (int /*<<< orphan*/ ) ; 
 scalar_t__ bgzf_flush (TYPE_1__*) ; 
 int deflate_block (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_cache (TYPE_1__*) ; 
 int fwrite (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

int bgzf_close(BGZF* fp)
{
	int ret, count, block_length;
	if (fp == 0) return -1;
	if (fp->open_mode == 'w') {
		if (bgzf_flush(fp) != 0) return -1;
		block_length = deflate_block(fp, 0); // write an empty block
		count = fwrite(fp->compressed_block, 1, block_length, fp->fp);
		if (fflush(fp->fp) != 0) {
			fp->errcode |= BGZF_ERR_IO;
			return -1;
		}
	}
	ret = fp->open_mode == 'w'? fclose(fp->fp) : _bgzf_close(fp->fp);
	if (ret != 0) return -1;
	free(fp->uncompressed_block);
	free(fp->compressed_block);
	free_cache(fp);
	free(fp);
	return 0;
}