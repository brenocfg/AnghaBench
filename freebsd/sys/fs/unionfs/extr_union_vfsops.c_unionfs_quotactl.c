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
typedef  int /*<<< orphan*/  uid_t ;
struct unionfs_mount {TYPE_1__* um_uppervp; } ;
struct mount {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 struct unionfs_mount* MOUNTTOUNIONFSMOUNT (struct mount*) ; 
 int VFS_QUOTACTL (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
unionfs_quotactl(struct mount *mp, int cmd, uid_t uid, void *arg)
{
	struct unionfs_mount *ump;

	ump = MOUNTTOUNIONFSMOUNT(mp);

	/*
	 * Writing is always performed to upper vnode.
	 */
	return (VFS_QUOTACTL(ump->um_uppervp->v_mount, cmd, uid, arg));
}