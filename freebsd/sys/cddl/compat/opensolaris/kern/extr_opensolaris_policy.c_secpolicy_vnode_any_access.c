#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  v_type; int /*<<< orphan*/  v_mount; } ;
typedef  TYPE_1__ vnode_t ;
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  privs ;
struct TYPE_8__ {scalar_t__ cr_uid; } ;
typedef  TYPE_2__ cred_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int EPERM ; 
#define  PRIV_VFS_ADMIN 132 
#define  PRIV_VFS_EXEC 131 
#define  PRIV_VFS_LOOKUP 130 
#define  PRIV_VFS_READ 129 
#define  PRIV_VFS_WRITE 128 
 int /*<<< orphan*/  VDIR ; 
 scalar_t__ priv_check_cred (TYPE_2__*,int) ; 
 scalar_t__ secpolicy_fs_owner (int /*<<< orphan*/ ,TYPE_2__*) ; 

int
secpolicy_vnode_any_access(cred_t *cr, vnode_t *vp, uid_t owner)
{
	static int privs[] = {
	    PRIV_VFS_ADMIN,
	    PRIV_VFS_READ,
	    PRIV_VFS_WRITE,
	    PRIV_VFS_EXEC,
	    PRIV_VFS_LOOKUP
	};
	int i;

	if (secpolicy_fs_owner(vp->v_mount, cr) == 0)
		return (0);

	/* Same as secpolicy_vnode_setdac */
	if (owner == cr->cr_uid)
		return (0);

	for (i = 0; i < sizeof (privs)/sizeof (int); i++) {
		boolean_t allzone = B_FALSE;
		int priv;

		switch (priv = privs[i]) {
		case PRIV_VFS_EXEC:
			if (vp->v_type == VDIR)
				continue;
			break;
		case PRIV_VFS_LOOKUP:
			if (vp->v_type != VDIR)
				continue;
			break;
		}
		if (priv_check_cred(cr, priv) == 0)
			return (0);
	}
	return (EPERM);
}