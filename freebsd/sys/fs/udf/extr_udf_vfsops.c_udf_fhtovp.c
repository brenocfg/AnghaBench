#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct udf_node {TYPE_1__* fentry; } ;
struct mount {int dummy; } ;
struct ifid {int /*<<< orphan*/  ifid_ino; } ;
struct fid {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  inf_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 struct vnode* NULLVP ; 
 int VFS_VGET (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode**) ; 
 struct udf_node* VTON (struct vnode*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_create_vobject (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udf_fhtovp(struct mount *mp, struct fid *fhp, int flags, struct vnode **vpp)
{
	struct ifid *ifhp;
	struct vnode *nvp;
	struct udf_node *np;
	off_t fsize;
	int error;

	ifhp = (struct ifid *)fhp;

	if ((error = VFS_VGET(mp, ifhp->ifid_ino, LK_EXCLUSIVE, &nvp)) != 0) {
		*vpp = NULLVP;
		return (error);
	}

	np = VTON(nvp);
	fsize = le64toh(np->fentry->inf_len);

	*vpp = nvp;
	vnode_create_vobject(*vpp, fsize, curthread);
	return (0);
}