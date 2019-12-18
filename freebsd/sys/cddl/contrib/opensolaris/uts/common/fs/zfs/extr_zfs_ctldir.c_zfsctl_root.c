#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  z_vfs; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int /*<<< orphan*/  vnode_t ;

/* Variables and functions */
 int zfsctl_root_vnode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

int
zfsctl_root(zfsvfs_t *zfsvfs, int flags, vnode_t **vpp)
{
	vnode_t *vp;
	int error;

	error = zfsctl_root_vnode(zfsvfs->z_vfs, NULL, flags, vpp);
	return (error);
}