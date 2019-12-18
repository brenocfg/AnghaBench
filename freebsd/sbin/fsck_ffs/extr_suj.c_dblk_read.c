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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct data_blk {int db_size; int /*<<< orphan*/ * db_buf; } ;

/* Variables and functions */
 int bread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct data_blk* dblk_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  err_suj (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * errmalloc (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  fsbtodb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t *
dblk_read(ufs2_daddr_t blk, int size)
{
	struct data_blk *dblk;

	dblk = dblk_lookup(blk);
	/*
	 * I doubt size mismatches can happen in practice but it is trivial
	 * to handle.
	 */
	if (size != dblk->db_size) {
		if (dblk->db_buf)
			free(dblk->db_buf);
		dblk->db_buf = errmalloc(size);
		dblk->db_size = size;
		if (bread(&disk, fsbtodb(fs, blk), dblk->db_buf, size) == -1)
			err_suj("Failed to read data block %jd\n", blk);
	}
	return (dblk->db_buf);
}