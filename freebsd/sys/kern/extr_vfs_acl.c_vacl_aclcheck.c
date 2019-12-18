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
 int /*<<< orphan*/  M_WAITOK ; 
 int VOP_ACLCHECK (struct vnode*,int /*<<< orphan*/ ,struct acl*,int /*<<< orphan*/ ,struct thread*) ; 
 struct acl* acl_alloc (int /*<<< orphan*/ ) ; 
 int acl_copyin (struct acl const*,struct acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_free (struct acl*) ; 
 int /*<<< orphan*/  acl_type_unold (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vacl_aclcheck(struct thread *td, struct vnode *vp, acl_type_t type,
    const struct acl *aclp)
{
	struct acl *inkernelacl;
	int error;

	inkernelacl = acl_alloc(M_WAITOK);
	error = acl_copyin(aclp, inkernelacl, type);
	if (error != 0)
		goto out;
	error = VOP_ACLCHECK(vp, acl_type_unold(type), inkernelacl,
	    td->td_ucred, td);
out:
	acl_free(inkernelacl);
	return (error);
}