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
struct acl {int dummy; } ;
typedef  int /*<<< orphan*/  acl_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (struct vnode*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int VOP_GETACL (struct vnode*,int /*<<< orphan*/ ,struct acl*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 struct acl* acl_alloc (int) ; 
 int acl_copyout (struct acl*,struct acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_free (struct acl*) ; 
 int /*<<< orphan*/  acl_type_unold (int /*<<< orphan*/ ) ; 
 int mac_vnode_check_getacl (int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
vacl_get_acl(struct thread *td, struct vnode *vp, acl_type_t type,
    struct acl *aclp)
{
	struct acl *inkernelacl;
	int error;

	AUDIT_ARG_VALUE(type);
	inkernelacl = acl_alloc(M_WAITOK | M_ZERO);
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	AUDIT_ARG_VNODE1(vp);
#ifdef MAC
	error = mac_vnode_check_getacl(td->td_ucred, vp, type);
	if (error != 0)
		goto out;
#endif
	error = VOP_GETACL(vp, acl_type_unold(type), inkernelacl,
	    td->td_ucred, td);

#ifdef MAC
out:
#endif
	VOP_UNLOCK(vp, 0);
	if (error == 0)
		error = acl_copyout(inkernelacl, aclp, type);
	acl_free(inkernelacl);
	return (error);
}