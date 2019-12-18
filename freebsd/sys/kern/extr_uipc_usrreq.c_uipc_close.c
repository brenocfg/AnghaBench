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
struct unpcb {struct unpcb* unp_conn; struct vnode* unp_vnode; } ;
struct socket {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int /*<<< orphan*/  VOP_UNP_DETACH (struct vnode*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 struct mtx* mtx_pool_find (int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_disconnect (struct unpcb*,struct unpcb*) ; 
 int /*<<< orphan*/  unp_pcb_hold (struct unpcb*) ; 
 int /*<<< orphan*/  unp_pcb_owned_lock2 (struct unpcb*,struct unpcb*,int) ; 
 scalar_t__ unp_pcb_rele (struct unpcb*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static void
uipc_close(struct socket *so)
{
	struct unpcb *unp, *unp2;
	struct vnode *vp = NULL;
	struct mtx *vplock;
	int freed;
	unp = sotounpcb(so);
	KASSERT(unp != NULL, ("uipc_close: unp == NULL"));


	vplock = NULL;
	if ((vp = unp->unp_vnode) != NULL) {
		vplock = mtx_pool_find(mtxpool_sleep, vp);
		mtx_lock(vplock);
	}
	UNP_PCB_LOCK(unp);
	if (vp && unp->unp_vnode == NULL) {
		mtx_unlock(vplock);
		vp = NULL;
	}
	if (vp != NULL) {
		VOP_UNP_DETACH(vp);
		unp->unp_vnode = NULL;
	}
	unp2 = unp->unp_conn;
	unp_pcb_hold(unp);
	if (__predict_false(unp == unp2)) {
		unp_disconnect(unp, unp2);
	} else if (unp2 != NULL) {
		unp_pcb_hold(unp2);
		unp_pcb_owned_lock2(unp, unp2, freed);
		unp_disconnect(unp, unp2);
		if (unp_pcb_rele(unp2) == 0)
			UNP_PCB_UNLOCK(unp2);
	}
	if (unp_pcb_rele(unp) == 0)
		UNP_PCB_UNLOCK(unp);
	if (vp) {
		mtx_unlock(vplock);
		vrele(vp);
	}
}