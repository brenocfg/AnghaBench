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
struct ufsmount {scalar_t__ um_fstype; } ;
struct inode {struct inode* i_din2; struct inode* i_din1; } ;

/* Variables and functions */
 scalar_t__ UFS1 ; 
 int /*<<< orphan*/  uma_inode ; 
 int /*<<< orphan*/  uma_ufs1 ; 
 int /*<<< orphan*/  uma_ufs2 ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct inode*) ; 

__attribute__((used)) static void
ffs_ifree(struct ufsmount *ump, struct inode *ip)
{

	if (ump->um_fstype == UFS1 && ip->i_din1 != NULL)
		uma_zfree(uma_ufs1, ip->i_din1);
	else if (ip->i_din2 != NULL)
		uma_zfree(uma_ufs2, ip->i_din2);
	uma_zfree(uma_inode, ip);
}