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
struct vop_vptofh_args {scalar_t__ a_fhp; int /*<<< orphan*/  a_vp; } ;
struct ufid {int ufid_len; int /*<<< orphan*/  ufid_gen; int /*<<< orphan*/  ufid_ino; } ;
struct inode {int /*<<< orphan*/  i_gen; int /*<<< orphan*/  i_number; } ;

/* Variables and functions */
 struct inode* VTOI (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffs_vptofh(struct vop_vptofh_args *ap)
/*
vop_vptofh {
	IN struct vnode *a_vp;
	IN struct fid *a_fhp;
};
*/
{
	struct inode *ip;
	struct ufid *ufhp;

	ip = VTOI(ap->a_vp);
	ufhp = (struct ufid *)ap->a_fhp;
	ufhp->ufid_len = sizeof(struct ufid);
	ufhp->ufid_ino = ip->i_number;
	ufhp->ufid_gen = ip->i_gen;
	return (0);
}