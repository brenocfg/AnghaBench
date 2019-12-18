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
struct vnode {scalar_t__ v_type; } ;
struct smbnode {int n_size; int /*<<< orphan*/  n_attrage; int /*<<< orphan*/  n_dosattr; int /*<<< orphan*/  n_mtime; } ;
struct smbfattr {int fa_size; int /*<<< orphan*/  fa_attr; int /*<<< orphan*/  fa_mtime; } ;

/* Variables and functions */
 scalar_t__ VDIR ; 
 scalar_t__ VREG ; 
 struct smbnode* VTOSMB (struct vnode*) ; 
 int /*<<< orphan*/  time_second ; 
 int /*<<< orphan*/  vnode_pager_setsize (struct vnode*,int) ; 

void
smbfs_attr_cacheenter(struct vnode *vp, struct smbfattr *fap)
{
	struct smbnode *np = VTOSMB(vp);

	if (vp->v_type == VREG) {
		if (np->n_size != fap->fa_size) {
			np->n_size = fap->fa_size;
			vnode_pager_setsize(vp, np->n_size);
		}
	} else if (vp->v_type == VDIR) {
		np->n_size = 16384; 		/* should be a better way ... */
	} else
		return;
	np->n_mtime = fap->fa_mtime;
	np->n_dosattr = fap->fa_attr;
	np->n_attrage = time_second;
	return;
}