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
struct vnode {int /*<<< orphan*/  v_label; } ;
struct mount {int dummy; } ;
struct devfs_dirent {int /*<<< orphan*/  de_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct mount*,struct devfs_dirent*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_update ; 

void
mac_devfs_update(struct mount *mp, struct devfs_dirent *de, struct vnode *vp)
{

	MAC_POLICY_PERFORM_NOSLEEP(devfs_update, mp, de, de->de_label, vp,
	    vp->v_label);
}