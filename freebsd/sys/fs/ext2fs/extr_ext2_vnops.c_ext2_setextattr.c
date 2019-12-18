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
struct vop_setextattr_args {int /*<<< orphan*/  a_uio; int /*<<< orphan*/  a_name; int /*<<< orphan*/  a_attrnamespace; int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_cred; TYPE_1__* a_vp; } ;
struct m_ext2fs {int dummy; } ;
struct inode {struct m_ext2fs* i_e2fs; } ;
struct TYPE_3__ {scalar_t__ v_type; } ;

/* Variables and functions */
 scalar_t__ E2FS_REV0_INODE_SIZE ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EXT2F_COMPAT_EXT_ATTR ; 
 int /*<<< orphan*/  EXT2_HAS_COMPAT_FEATURE (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_INODE_SIZE (struct m_ext2fs*) ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 struct inode* VTOI (TYPE_1__*) ; 
 int /*<<< orphan*/  VWRITE ; 
 int ext2_extattr_block_set (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext2_extattr_inode_set (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext2_extattr_valid_attrname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int extattr_check_cred (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_setextattr(struct vop_setextattr_args *ap)
{
	struct inode *ip;
	struct m_ext2fs *fs;
	int error;

	ip = VTOI(ap->a_vp);
	fs = ip->i_e2fs;

	if (!EXT2_HAS_COMPAT_FEATURE(ip->i_e2fs, EXT2F_COMPAT_EXT_ATTR))
		return (EOPNOTSUPP);

	if (ap->a_vp->v_type == VCHR || ap->a_vp->v_type == VBLK)
		return (EOPNOTSUPP);

	error = extattr_check_cred(ap->a_vp, ap->a_attrnamespace,
	    ap->a_cred, ap->a_td, VWRITE);
	if (error)
		return (error);

	error = ext2_extattr_valid_attrname(ap->a_attrnamespace, ap->a_name);
	if (error)
		return (error);

	if (EXT2_INODE_SIZE(fs) != E2FS_REV0_INODE_SIZE) {
		error = ext2_extattr_inode_set(ip, ap->a_attrnamespace,
		    ap->a_name, ap->a_uio);
		if (error != ENOSPC)
			return (error);
	}

	error = ext2_extattr_block_set(ip, ap->a_attrnamespace,
	    ap->a_name, ap->a_uio);

	return (error);
}