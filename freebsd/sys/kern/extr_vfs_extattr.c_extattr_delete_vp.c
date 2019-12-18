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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int PCATCH ; 
 int VOP_DELETEEXTATTR (struct vnode*,int,char const*,int /*<<< orphan*/ ,struct thread*) ; 
 int VOP_SETEXTATTR (struct vnode*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int V_WAIT ; 
 int mac_vnode_check_deleteextattr (int /*<<< orphan*/ ,struct vnode*,int,char const*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 

__attribute__((used)) static int
extattr_delete_vp(struct vnode *vp, int attrnamespace, const char *attrname,
    struct thread *td)
{
	struct mount *mp;
	int error;

	error = vn_start_write(vp, &mp, V_WAIT | PCATCH);
	if (error)
		return (error);
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);

#ifdef MAC
	error = mac_vnode_check_deleteextattr(td->td_ucred, vp, attrnamespace,
	    attrname);
	if (error)
		goto done;
#endif

	error = VOP_DELETEEXTATTR(vp, attrnamespace, attrname, td->td_ucred,
	    td);
	if (error == EOPNOTSUPP)
		error = VOP_SETEXTATTR(vp, attrnamespace, attrname, NULL,
		    td->td_ucred, td);
#ifdef MAC
done:
#endif
	VOP_UNLOCK(vp, 0);
	vn_finished_write(mp);
	return (error);
}