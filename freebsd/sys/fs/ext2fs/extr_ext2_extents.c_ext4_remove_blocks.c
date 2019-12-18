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
struct inode {int dummy; } ;
struct ext4_extent {unsigned long e_blk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_ext_blkfree (struct inode*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long ext4_ext_extent_pblock (struct ext4_extent*) ; 
 unsigned long ext4_ext_get_actual_len (struct ext4_extent*) ; 

__attribute__((used)) static int
ext4_remove_blocks(struct inode *ip, struct ext4_extent *ex,
    unsigned long from, unsigned long to)
{
	unsigned long num, start;

	if (from >= ex->e_blk &&
	    to == ex->e_blk + ext4_ext_get_actual_len(ex) - 1) {
		/* Tail cleanup. */
		num = ex->e_blk + ext4_ext_get_actual_len(ex) - from;
		start = ext4_ext_extent_pblock(ex) +
		    ext4_ext_get_actual_len(ex) - num;
		ext4_ext_blkfree(ip, start, num, 0);
	}

	return (0);
}