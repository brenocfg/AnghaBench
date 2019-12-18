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
struct acl {int dummy; } ;
typedef  int /*<<< orphan*/  acl_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (struct vnode*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PCATCH ; 
 int VOP_SETACL (struct vnode*,int /*<<< orphan*/ ,struct acl*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int V_WAIT ; 
 struct acl* acl_alloc (int /*<<< orphan*/ ) ; 
 int acl_copyin (struct acl const*,struct acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_free (struct acl*) ; 
 int /*<<< orphan*/  acl_type_unold (int /*<<< orphan*/ ) ; 
 int mac_vnode_check_setacl (int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,struct acl*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 

__attribute__((used)) static int
vacl_set_acl(struct thread *td, struct vnode *vp, acl_type_t type,
    const struct acl *aclp)
{
	struct acl *inkernelacl;
	struct mount *mp;
	int error;

	AUDIT_ARG_VALUE(type);
	inkernelacl = acl_alloc(M_WAITOK);
	error = acl_copyin(aclp, inkernelacl, type);
	if (error != 0)
		goto out;
	error = vn_start_write(vp, &mp, V_WAIT | PCATCH);
	if (error != 0)
		goto out;
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	AUDIT_ARG_VNODE1(vp);
#ifdef MAC
	error = mac_vnode_check_setacl(td->td_ucred, vp, type, inkernelacl);
	if (error != 0)
		goto out_unlock;
#endif
	error = VOP_SETACL(vp, acl_type_unold(type), inkernelacl,
	    td->td_ucred, td);
#ifdef MAC
out_unlock:
#endif
	VOP_UNLOCK(vp, 0);
	vn_finished_write(mp);
out:
	acl_free(inkernelacl);
	return (error);
}