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
struct vnode {int dummy; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int EOPNOTSUPP ; 
 int IO_NODELOCKED ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int VOP_DELETEEXTATTR (struct vnode*,int,char const*,int /*<<< orphan*/ *,struct thread*) ; 
 int VOP_SETEXTATTR (struct vnode*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_WAIT ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int vn_start_write (struct vnode*,struct mount**,int /*<<< orphan*/ ) ; 

int
vn_extattr_rm(struct vnode *vp, int ioflg, int attrnamespace,
    const char *attrname, struct thread *td)
{
	struct mount	*mp;
	int	error;

	if ((ioflg & IO_NODELOCKED) == 0) {
		if ((error = vn_start_write(vp, &mp, V_WAIT)) != 0)
			return (error);
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	}

	ASSERT_VOP_LOCKED(vp, "IO_NODELOCKED with no vp lock held");

	/* authorize attribute removal as kernel */
	error = VOP_DELETEEXTATTR(vp, attrnamespace, attrname, NULL, td);
	if (error == EOPNOTSUPP)
		error = VOP_SETEXTATTR(vp, attrnamespace, attrname, NULL,
		    NULL, td);

	if ((ioflg & IO_NODELOCKED) == 0) {
		vn_finished_write(mp);
		VOP_UNLOCK(vp, 0);
	}

	return (error);
}