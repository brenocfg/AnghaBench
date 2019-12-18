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
struct vnode {int /*<<< orphan*/  v_label; } ;
struct ucred {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK (int /*<<< orphan*/ ,struct ucred*,struct vnode*,int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  NOCRED ; 
 int VOP_CLOSEEXTATTR (struct vnode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VOP_OPENEXTATTR (struct vnode*,struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int ea_warn_once ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vnode_setlabel_extattr ; 

__attribute__((used)) static int
mac_vnode_setlabel_extattr(struct ucred *cred, struct vnode *vp,
    struct label *intlabel)
{
	int error;

	ASSERT_VOP_LOCKED(vp, "mac_vnode_setlabel_extattr");

	error = VOP_OPENEXTATTR(vp, cred, curthread);
	if (error == EOPNOTSUPP) {
		if (ea_warn_once == 0) {
			printf("Warning: transactions not supported "
			    "in EA write.\n");
			ea_warn_once = 1;
		}
	} else if (error)
		return (error);

	MAC_POLICY_CHECK(vnode_setlabel_extattr, cred, vp, vp->v_label,
	    intlabel);

	if (error) {
		VOP_CLOSEEXTATTR(vp, 0, NOCRED, curthread);
		return (error);
	}

	error = VOP_CLOSEEXTATTR(vp, 1, NOCRED, curthread);
	if (error == EOPNOTSUPP)
		error = 0;

	return (error);
}