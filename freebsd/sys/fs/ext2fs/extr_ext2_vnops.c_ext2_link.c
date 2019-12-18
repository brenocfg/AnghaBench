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
struct vop_link_args {struct componentname* a_cnp; struct vnode* a_tdvp; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct inode {int i_flags; int /*<<< orphan*/  i_flag; scalar_t__ i_nlink; } ;
struct componentname {int cn_flags; } ;
typedef  scalar_t__ nlink_t ;

/* Variables and functions */
 int APPEND ; 
 int /*<<< orphan*/  DOINGASYNC (struct vnode*) ; 
 int EMLINK ; 
 int EPERM ; 
 scalar_t__ EXT4_LINK_MAX ; 
 int HASBUF ; 
 int IMMUTABLE ; 
 int /*<<< orphan*/  IN_CHANGE ; 
 struct inode* VTOI (struct vnode*) ; 
 int ext2_direnter (struct inode*,struct vnode*,struct componentname*) ; 
 int ext2_update (struct vnode*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
ext2_link(struct vop_link_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vnode *tdvp = ap->a_tdvp;
	struct componentname *cnp = ap->a_cnp;
	struct inode *ip;
	int error;

#ifdef INVARIANTS
	if ((cnp->cn_flags & HASBUF) == 0)
		panic("ext2_link: no name");
#endif
	ip = VTOI(vp);
	if ((nlink_t)ip->i_nlink >= EXT4_LINK_MAX) {
		error = EMLINK;
		goto out;
	}
	if (ip->i_flags & (IMMUTABLE | APPEND)) {
		error = EPERM;
		goto out;
	}
	ip->i_nlink++;
	ip->i_flag |= IN_CHANGE;
	error = ext2_update(vp, !DOINGASYNC(vp));
	if (!error)
		error = ext2_direnter(ip, tdvp, cnp);
	if (error) {
		ip->i_nlink--;
		ip->i_flag |= IN_CHANGE;
	}
out:
	return (error);
}