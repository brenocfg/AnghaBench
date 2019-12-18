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
struct ng_bt_mbufq {int dummy; } ;
struct udbp_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; struct ng_bt_mbufq sc_xmitq; struct ng_bt_mbufq sc_xmitq_hipri; } ;
struct ng_tag_prio {scalar_t__ priority; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int EHOSTDOWN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NG_BT_MBUFQ_DROP (struct ng_bt_mbufq*) ; 
 int /*<<< orphan*/  NG_BT_MBUFQ_ENQUEUE (struct ng_bt_mbufq*,struct mbuf*) ; 
 scalar_t__ NG_BT_MBUFQ_FULL (struct ng_bt_mbufq*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 struct udbp_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_PRIO_CUTOFF ; 
 int /*<<< orphan*/  NG_TAG_PRIO ; 
 size_t UDBP_T_WR ; 
 scalar_t__ m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_udbp_rcvdata(hook_p hook, item_p item)
{
	struct udbp_softc *sc = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	struct ng_bt_mbufq *queue_ptr;
	struct mbuf *m;
	struct ng_tag_prio *ptag;
	int error;

	if (sc == NULL) {
		NG_FREE_ITEM(item);
		return (EHOSTDOWN);
	}
	NGI_GET_M(item, m);
	NG_FREE_ITEM(item);

	/*
	 * Now queue the data for when it can be sent
	 */
	ptag = (void *)m_tag_locate(m, NGM_GENERIC_COOKIE,
	    NG_TAG_PRIO, NULL);

	if (ptag && (ptag->priority > NG_PRIO_CUTOFF))
		queue_ptr = &sc->sc_xmitq_hipri;
	else
		queue_ptr = &sc->sc_xmitq;

	mtx_lock(&sc->sc_mtx);

	if (NG_BT_MBUFQ_FULL(queue_ptr)) {
		NG_BT_MBUFQ_DROP(queue_ptr);
		NG_FREE_M(m);
		error = ENOBUFS;
	} else {
		NG_BT_MBUFQ_ENQUEUE(queue_ptr, m);
		/*
		 * start bulk-out transfer, if not already started:
		 */
		usbd_transfer_start(sc->sc_xfer[UDBP_T_WR]);
		error = 0;
	}

	mtx_unlock(&sc->sc_mtx);

	return (error);
}