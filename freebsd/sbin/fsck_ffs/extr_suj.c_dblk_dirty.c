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
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct data_blk {int db_dirty; } ;

/* Variables and functions */
 struct data_blk* dblk_lookup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dblk_dirty(ufs2_daddr_t blk)
{
	struct data_blk *dblk;

	dblk = dblk_lookup(blk);
	dblk->db_dirty = 1;
}