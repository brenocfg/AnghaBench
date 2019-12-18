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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  accmode_t ;

/* Variables and functions */
 int EPERM ; 
#define  EXTATTR_NAMESPACE_SYSTEM 129 
#define  EXTATTR_NAMESPACE_USER 128 
 struct ucred* NOCRED ; 
 int /*<<< orphan*/  PRIV_VFS_EXTATTR_SYSTEM ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 

int
extattr_check_cred(struct vnode *vp, int attrnamespace, struct ucred *cred,
    struct thread *td, accmode_t accmode)
{

	/*
	 * Kernel-invoked always succeeds.
	 */
	if (cred == NOCRED)
		return (0);

	/*
	 * Do not allow privileged processes in jail to directly manipulate
	 * system attributes.
	 */
	switch (attrnamespace) {
	case EXTATTR_NAMESPACE_SYSTEM:
		/* Potentially should be: return (EPERM); */
		return (priv_check_cred(cred, PRIV_VFS_EXTATTR_SYSTEM));
	case EXTATTR_NAMESPACE_USER:
		return (VOP_ACCESS(vp, accmode, cred, td));
	default:
		return (EPERM);
	}
}