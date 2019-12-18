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
struct vop_read_args {int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_ioflag; int /*<<< orphan*/  a_uio; struct vnode* a_vp; } ;
struct vnode {int v_type; } ;

/* Variables and functions */
 int EISDIR ; 
 int EOPNOTSUPP ; 
#define  VDIR 129 
#define  VREG 128 
 int ncl_bioread (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_read(struct vop_read_args *ap)
{
	struct vnode *vp = ap->a_vp;

	switch (vp->v_type) {
	case VREG:
		return (ncl_bioread(vp, ap->a_uio, ap->a_ioflag, ap->a_cred));
	case VDIR:
		return (EISDIR);
	default:
		return (EOPNOTSUPP);
	}
}