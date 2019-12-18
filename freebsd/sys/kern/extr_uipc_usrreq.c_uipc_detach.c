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
struct unpcb {int unp_flags; TYPE_1__* unp_socket; struct sockaddr_un* unp_addr; int /*<<< orphan*/  unp_refs; struct unpcb* unp_conn; struct vnode* unp_vnode; scalar_t__ unp_gencnt; } ;
struct socket {int dummy; } ;
struct sockaddr_un {int dummy; } ;
struct mtx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * so_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct unpcb* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct unpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  UNP_LINK_WLOCK () ; 
 int /*<<< orphan*/  UNP_LINK_WUNLOCK () ; 
 int UNP_NASCENT ; 
 int /*<<< orphan*/  UNP_PCB_LOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_PCB_UNLOCK_ASSERT (struct unpcb*) ; 
 int /*<<< orphan*/  UNP_REF_LIST_LOCK () ; 
 int /*<<< orphan*/  UNP_REF_LIST_UNLOCK () ; 
 int /*<<< orphan*/  VOP_UNP_DETACH (struct vnode*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  free (struct sockaddr_un*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 struct mtx* mtx_pool_find (int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  unp_count ; 
 int /*<<< orphan*/  unp_disconnect (struct unpcb*,struct unpcb*) ; 
 int /*<<< orphan*/  unp_drop (struct unpcb*) ; 
 int /*<<< orphan*/  unp_gc_task ; 
 scalar_t__ unp_gencnt ; 
 int /*<<< orphan*/  unp_link ; 
 int /*<<< orphan*/  unp_pcb_hold (struct unpcb*) ; 
 int /*<<< orphan*/  unp_pcb_owned_lock2 (struct unpcb*,struct unpcb*,int) ; 
 scalar_t__ unp_pcb_rele (struct unpcb*) ; 
 int unp_rights ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static void
uipc_detach(struct socket *so)
{
	struct unpcb *unp, *unp2;
	struct mtx *vplock;
	struct sockaddr_un *saved_unp_addr;
	struct vnode *vp;
	int freeunp, local_unp_rights;

	unp = sotounpcb(so);
	KASSERT(unp != NULL, ("uipc_detach: unp == NULL"));

	vp = NULL;
	vplock = NULL;
	local_unp_rights = 0;

	UNP_LINK_WLOCK();
	LIST_REMOVE(unp, unp_link);
	unp->unp_gencnt = ++unp_gencnt;
	--unp_count;
	UNP_LINK_WUNLOCK();

	UNP_PCB_UNLOCK_ASSERT(unp);
 restart:
	if ((vp = unp->unp_vnode) != NULL) {
		vplock = mtx_pool_find(mtxpool_sleep, vp);
		mtx_lock(vplock);
	}
	UNP_PCB_LOCK(unp);
	if (unp->unp_vnode != vp &&
		unp->unp_vnode != NULL) {
		if (vplock)
			mtx_unlock(vplock);
		UNP_PCB_UNLOCK(unp);
		goto restart;
	}
	if ((unp->unp_flags & UNP_NASCENT) != 0) {
		goto teardown;
	}
	if ((vp = unp->unp_vnode) != NULL) {
		VOP_UNP_DETACH(vp);
		unp->unp_vnode = NULL;
	}
	if (__predict_false(unp == unp->unp_conn)) {
		unp_disconnect(unp, unp);
		unp2 = NULL;
		goto connect_self;
	}
	if ((unp2 = unp->unp_conn) != NULL) {
		unp_pcb_owned_lock2(unp, unp2, freeunp);
		if (freeunp)
			unp2 = NULL;
	}
	unp_pcb_hold(unp);
	if (unp2 != NULL) {
		unp_pcb_hold(unp2);
		unp_disconnect(unp, unp2);
		if (unp_pcb_rele(unp2) == 0)
			UNP_PCB_UNLOCK(unp2);
	}
 connect_self:
	UNP_PCB_UNLOCK(unp);
	UNP_REF_LIST_LOCK();
	while (!LIST_EMPTY(&unp->unp_refs)) {
		struct unpcb *ref = LIST_FIRST(&unp->unp_refs);

		unp_pcb_hold(ref);
		UNP_REF_LIST_UNLOCK();

		MPASS(ref != unp);
		UNP_PCB_UNLOCK_ASSERT(ref);
		unp_drop(ref);
		UNP_REF_LIST_LOCK();
	}

	UNP_REF_LIST_UNLOCK();
	UNP_PCB_LOCK(unp);
	freeunp = unp_pcb_rele(unp);
	MPASS(freeunp == 0);
	local_unp_rights = unp_rights;
teardown:
	unp->unp_socket->so_pcb = NULL;
	saved_unp_addr = unp->unp_addr;
	unp->unp_addr = NULL;
	unp->unp_socket = NULL;
	freeunp = unp_pcb_rele(unp);
	if (saved_unp_addr != NULL)
		free(saved_unp_addr, M_SONAME);
	if (!freeunp)
		UNP_PCB_UNLOCK(unp);
	if (vp) {
		mtx_unlock(vplock);
		vrele(vp);
	}
	if (local_unp_rights)
		taskqueue_enqueue_timeout(taskqueue_thread, &unp_gc_task, -1);
}