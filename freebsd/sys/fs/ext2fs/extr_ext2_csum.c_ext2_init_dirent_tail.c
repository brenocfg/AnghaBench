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
struct ext2fs_direct_tail {int e2dt_rec_len; int /*<<< orphan*/  e2dt_reserved_ft; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_FT_DIR_CSUM ; 
 int /*<<< orphan*/  memset (struct ext2fs_direct_tail*,int /*<<< orphan*/ ,int) ; 

void
ext2_init_dirent_tail(struct ext2fs_direct_tail *tp)
{
	memset(tp, 0, sizeof(struct ext2fs_direct_tail));
	tp->e2dt_rec_len = sizeof(struct ext2fs_direct_tail);
	tp->e2dt_reserved_ft = EXT2_FT_DIR_CSUM;
}