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
struct TYPE_3__ {scalar_t__ v_type; int /*<<< orphan*/  v_mount; } ;
typedef  TYPE_1__ vnode_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int accmode_t ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  PRIV_VFS_EXEC ; 
 int /*<<< orphan*/  PRIV_VFS_LOOKUP ; 
 int /*<<< orphan*/  PRIV_VFS_READ ; 
 int /*<<< orphan*/  PRIV_VFS_WRITE ; 
 scalar_t__ VDIR ; 
 int VEXEC ; 
 int VREAD ; 
 int VWRITE ; 
 scalar_t__ priv_check_cred (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ secpolicy_fs_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
secpolicy_vnode_access(cred_t *cr, vnode_t *vp, uid_t owner, accmode_t accmode)
{

	if (secpolicy_fs_owner(vp->v_mount, cr) == 0)
		return (0);

	if ((accmode & VREAD) && priv_check_cred(cr, PRIV_VFS_READ) != 0)
		return (EACCES);
	if ((accmode & VWRITE) &&
	    priv_check_cred(cr, PRIV_VFS_WRITE) != 0) {
		return (EACCES);
	}
	if (accmode & VEXEC) {
		if (vp->v_type == VDIR) {
			if (priv_check_cred(cr, PRIV_VFS_LOOKUP) != 0)
				return (EACCES);
		} else {
			if (priv_check_cred(cr, PRIV_VFS_EXEC) != 0)
				return (EACCES);
		}
	}
	return (0);
}