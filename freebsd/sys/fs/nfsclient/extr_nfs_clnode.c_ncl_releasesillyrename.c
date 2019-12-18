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
struct thread {int dummy; } ;
struct sillyrename {int /*<<< orphan*/  s_task; int /*<<< orphan*/  s_cred; } ;
struct nfsnode {struct sillyrename* n_sillyrename; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  NFSASSERTNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sillyrename*) ; 
 scalar_t__ VDIR ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncl_removeit (struct sillyrename*,struct vnode*) ; 
 int /*<<< orphan*/  ncl_vinvalbuf (struct vnode*,int /*<<< orphan*/ ,struct thread*,int) ; 
 int /*<<< orphan*/  nfs_freesillyrename ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static void
ncl_releasesillyrename(struct vnode *vp, struct thread *td)
{
	struct nfsnode *np;
	struct sillyrename *sp;

	ASSERT_VOP_ELOCKED(vp, "releasesillyrename");
	np = VTONFS(vp);
	NFSASSERTNODE(np);
	if (vp->v_type != VDIR) {
		sp = np->n_sillyrename;
		np->n_sillyrename = NULL;
	} else
		sp = NULL;
	if (sp != NULL) {
		NFSUNLOCKNODE(np);
		(void) ncl_vinvalbuf(vp, 0, td, 1);
		/*
		 * Remove the silly file that was rename'd earlier
		 */
		ncl_removeit(sp, vp);
		crfree(sp->s_cred);
		TASK_INIT(&sp->s_task, 0, nfs_freesillyrename, sp);
		taskqueue_enqueue(taskqueue_thread, &sp->s_task);
		NFSLOCKNODE(np);
	}
}