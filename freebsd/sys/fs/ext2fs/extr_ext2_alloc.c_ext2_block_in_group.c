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
struct m_ext2fs {int dummy; } ;
typedef  int /*<<< orphan*/  e4fs_daddr_t ;

/* Variables and functions */
 int ext2_get_group_number (struct m_ext2fs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_block_in_group(struct m_ext2fs *fs, e4fs_daddr_t block, int cg)
{

	return ((ext2_get_group_number(fs, block) == cg) ? 1 : 0);
}