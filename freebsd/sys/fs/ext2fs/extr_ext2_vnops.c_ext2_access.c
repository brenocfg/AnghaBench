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
struct vop_access_args {int a_accmode; int /*<<< orphan*/  a_cred; struct vnode* a_vp; } ;
struct vnode {int v_type; TYPE_1__* v_mount; } ;
struct inode {int i_flags; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
typedef  int accmode_t ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 int EROFS ; 
 int MNT_RDONLY ; 
 int SF_IMMUTABLE ; 
 int SF_SNAPSHOT ; 
 int VBLK ; 
 int VCHR ; 
#define  VDIR 130 
#define  VLNK 129 
#define  VREG 128 
 struct inode* VTOI (struct vnode*) ; 
 int VWRITE ; 
 int vaccess (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ext2_access(struct vop_access_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct inode *ip = VTOI(vp);
	accmode_t accmode = ap->a_accmode;
	int error;

	if (vp->v_type == VBLK || vp->v_type == VCHR)
		return (EOPNOTSUPP);

	/*
	 * Disallow write attempts on read-only file systems;
	 * unless the file is a socket, fifo, or a block or
	 * character device resident on the file system.
	 */
	if (accmode & VWRITE) {
		switch (vp->v_type) {
		case VDIR:
		case VLNK:
		case VREG:
			if (vp->v_mount->mnt_flag & MNT_RDONLY)
				return (EROFS);
			break;
		default:
			break;
		}
	}

	/* If immutable bit set, nobody gets to write it. */
	if ((accmode & VWRITE) && (ip->i_flags & (SF_IMMUTABLE | SF_SNAPSHOT)))
		return (EPERM);

	error = vaccess(vp->v_type, ip->i_mode, ip->i_uid, ip->i_gid,
	    ap->a_accmode, ap->a_cred, NULL);
	return (error);
}