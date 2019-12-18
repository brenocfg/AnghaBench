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
struct vop_getpages_args {int /*<<< orphan*/  a_rahead; int /*<<< orphan*/  a_rbehind; int /*<<< orphan*/  a_count; int /*<<< orphan*/  a_m; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 int /*<<< orphan*/  cd9660_gbp_getblkno ; 
 int /*<<< orphan*/  cd9660_gbp_getblksz ; 
 scalar_t__ use_buf_pager ; 
 int vfs_bio_getpages (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vnode_pager_generic_getpages (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cd9660_getpages(struct vop_getpages_args *ap)
{
	struct vnode *vp;

	vp = ap->a_vp;
	if (vp->v_type == VCHR || vp->v_type == VBLK)
		return (EOPNOTSUPP);

	if (use_buf_pager)
		return (vfs_bio_getpages(vp, ap->a_m, ap->a_count,
		    ap->a_rbehind, ap->a_rahead, cd9660_gbp_getblkno,
		    cd9660_gbp_getblksz));
	return (vnode_pager_generic_getpages(vp, ap->a_m, ap->a_count,
	    ap->a_rbehind, ap->a_rahead, NULL, NULL));
}