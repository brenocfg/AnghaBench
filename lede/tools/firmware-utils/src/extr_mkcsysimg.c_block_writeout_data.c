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
struct csys_block {size_t size_avail; size_t file_size; int /*<<< orphan*/  css; int /*<<< orphan*/  padc; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,size_t) ; 
 int block_writeout_file (int /*<<< orphan*/ *,struct csys_block*) ; 
 int write_out_padding (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
block_writeout_data(FILE *outfile, struct csys_block *block)
{
	int res;
	size_t padlen;

	res = block_writeout_file(outfile, block);
	if (res)
		return res;

	/* write padding data if neccesary */
	padlen = block->size_avail - block->file_size;
	DBG(1,"padding block, length=%zu", padlen);
	res = write_out_padding(outfile, padlen, block->padc, block->css);

	return res;
}