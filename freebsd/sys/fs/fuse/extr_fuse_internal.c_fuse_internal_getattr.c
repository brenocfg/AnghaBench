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
struct vattr {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 struct vattr* VTOVA (struct vnode*) ; 
 int fuse_internal_do_getattr (struct vnode*,struct vattr*,struct ucred*,struct thread*) ; 

int
fuse_internal_getattr(struct vnode *vp, struct vattr *vap, struct ucred *cred,
	struct thread *td)
{
	struct vattr *attrs;

	if ((attrs = VTOVA(vp)) != NULL) {
		*vap = *attrs;	/* struct copy */
		return 0;
	}

	return fuse_internal_do_getattr(vp, vap, cred, td);
}