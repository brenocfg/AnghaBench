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
struct nfsnode {scalar_t__ n_attrstamp; TYPE_1__* n_accesscache; } ;
struct TYPE_2__ {scalar_t__ stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDTRACE_NFS_ACCESSCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  KDTRACE_NFS_ATTRCACHE_FLUSH_DONE (struct vnode*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int NFS_ACCESSCACHESIZE ; 
 struct nfsnode* VTONFS (struct vnode*) ; 

void
ncl_invalcaches(struct vnode *vp)
{
	struct nfsnode *np = VTONFS(vp);
	int i;

	NFSLOCKNODE(np);
	for (i = 0; i < NFS_ACCESSCACHESIZE; i++)
		np->n_accesscache[i].stamp = 0;
	KDTRACE_NFS_ACCESSCACHE_FLUSH_DONE(vp);
	np->n_attrstamp = 0;
	KDTRACE_NFS_ATTRCACHE_FLUSH_DONE(vp);
	NFSUNLOCKNODE(np);
}