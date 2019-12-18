#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct m_ext2fs {int e2fs_bsize; TYPE_1__* e2fs; } ;
typedef  int e4fs_daddr_t ;
struct TYPE_2__ {int e2fs_first_dblock; } ;

/* Variables and functions */

__attribute__((used)) static int
ext2_get_group_number(struct m_ext2fs *fs, e4fs_daddr_t block)
{

	return ((block - fs->e2fs->e2fs_first_dblock) / fs->e2fs_bsize);
}