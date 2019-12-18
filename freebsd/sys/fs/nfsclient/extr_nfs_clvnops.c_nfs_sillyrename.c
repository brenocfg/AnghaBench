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
struct sillyrename {int /*<<< orphan*/  s_cred; struct vnode* s_dvp; int /*<<< orphan*/  s_namlen; int /*<<< orphan*/  s_name; } ;
struct nfsnode {struct sillyrename* n_sillyrename; } ;
struct componentname {TYPE_2__* cn_thread; int /*<<< orphan*/  cn_cred; } ;
struct TYPE_4__ {TYPE_1__* td_proc; } ;
struct TYPE_3__ {short p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_NEWNFSREQ ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VREF (struct vnode*) ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sillyrename*,int /*<<< orphan*/ ) ; 
 struct sillyrename* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_lookitup (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,struct nfsnode**) ; 
 int nfs_renameit (struct vnode*,struct vnode*,struct componentname*,struct sillyrename*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned int,short) ; 
 scalar_t__ ticks ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
nfs_sillyrename(struct vnode *dvp, struct vnode *vp, struct componentname *cnp)
{
	struct sillyrename *sp;
	struct nfsnode *np;
	int error;
	short pid;
	unsigned int lticks;

	cache_purge(dvp);
	np = VTONFS(vp);
	KASSERT(vp->v_type != VDIR, ("nfs: sillyrename dir"));
	sp = malloc(sizeof (struct sillyrename),
	    M_NEWNFSREQ, M_WAITOK);
	sp->s_cred = crhold(cnp->cn_cred);
	sp->s_dvp = dvp;
	VREF(dvp);

	/* 
	 * Fudge together a funny name.
	 * Changing the format of the funny name to accommodate more 
	 * sillynames per directory.
	 * The name is now changed to .nfs.<ticks>.<pid>.4, where ticks is 
	 * CPU ticks since boot.
	 */
	pid = cnp->cn_thread->td_proc->p_pid;
	lticks = (unsigned int)ticks;
	for ( ; ; ) {
		sp->s_namlen = sprintf(sp->s_name, 
				       ".nfs.%08x.%04x4.4", lticks, 
				       pid);
		if (nfs_lookitup(dvp, sp->s_name, sp->s_namlen, sp->s_cred,
				 cnp->cn_thread, NULL))
			break;
		lticks++;
	}
	error = nfs_renameit(dvp, vp, cnp, sp);
	if (error)
		goto bad;
	error = nfs_lookitup(dvp, sp->s_name, sp->s_namlen, sp->s_cred,
		cnp->cn_thread, &np);
	np->n_sillyrename = sp;
	return (0);
bad:
	vrele(sp->s_dvp);
	crfree(sp->s_cred);
	free(sp, M_NEWNFSREQ);
	return (error);
}