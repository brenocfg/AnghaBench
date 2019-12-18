#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnode {scalar_t__ v_type; } ;
struct TYPE_3__ {scalar_t__* nfsuquad; } ;
struct nfsnode {int /*<<< orphan*/  n_cookies; TYPE_1__ n_cookieverf; scalar_t__ n_direofoffset; } ;
struct TYPE_4__ {scalar_t__ ndm_eocookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ VDIR ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  ncl_dircookie_lock (struct nfsnode*) ; 
 int /*<<< orphan*/  ncl_dircookie_unlock (struct nfsnode*) ; 

void
ncl_invaldir(struct vnode *vp)
{
	struct nfsnode *np = VTONFS(vp);

	KASSERT(vp->v_type == VDIR, ("nfs: invaldir not dir"));
	ncl_dircookie_lock(np);
	np->n_direofoffset = 0;
	np->n_cookieverf.nfsuquad[0] = 0;
	np->n_cookieverf.nfsuquad[1] = 0;
	if (LIST_FIRST(&np->n_cookies))
		LIST_FIRST(&np->n_cookies)->ndm_eocookie = 0;
	ncl_dircookie_unlock(np);
}