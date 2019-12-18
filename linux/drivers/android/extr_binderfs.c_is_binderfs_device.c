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
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {scalar_t__ s_magic; } ;

/* Variables and functions */
 scalar_t__ BINDERFS_SUPER_MAGIC ; 

bool is_binderfs_device(const struct inode *inode)
{
	if (inode->i_sb->s_magic == BINDERFS_SUPER_MAGIC)
		return true;

	return false;
}