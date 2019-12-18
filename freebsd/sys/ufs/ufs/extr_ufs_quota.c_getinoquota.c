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
struct vnode {int v_vflag; int /*<<< orphan*/  v_mount; } ;
struct ufsmount {int dummy; } ;
struct inode {int /*<<< orphan*/ * i_dquot; scalar_t__ i_gid; scalar_t__ i_uid; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t GRPQUOTA ; 
 struct vnode* ITOV (struct inode*) ; 
 size_t USRQUOTA ; 
 struct ufsmount* VFSTOUFS (int /*<<< orphan*/ ) ; 
 int VV_SYSTEM ; 
 int dqget (struct vnode*,scalar_t__,struct ufsmount*,size_t,int /*<<< orphan*/ *) ; 

int
getinoquota(struct inode *ip)
{
	struct ufsmount *ump;
	struct vnode *vp;
	int error;

	vp = ITOV(ip);

	/*
	 * Disk quotas must be turned off for system files.  Currently
	 * snapshot and quota files.
	 */
	if ((vp->v_vflag & VV_SYSTEM) != 0)
		return (0);
	/*
	 * XXX: Turn off quotas for files with a negative UID or GID.
	 * This prevents the creation of 100GB+ quota files.
	 */
	if ((int)ip->i_uid < 0 || (int)ip->i_gid < 0)
		return (0);
	ump = VFSTOUFS(vp->v_mount);
	/*
	 * Set up the user quota based on file uid.
	 * EINVAL means that quotas are not enabled.
	 */
	if ((error =
		dqget(vp, ip->i_uid, ump, USRQUOTA, &ip->i_dquot[USRQUOTA])) &&
	    error != EINVAL)
		return (error);
	/*
	 * Set up the group quota based on file gid.
	 * EINVAL means that quotas are not enabled.
	 */
	if ((error =
		dqget(vp, ip->i_gid, ump, GRPQUOTA, &ip->i_dquot[GRPQUOTA])) &&
	    error != EINVAL)
		return (error);
	return (0);
}