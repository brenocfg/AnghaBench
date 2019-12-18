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
struct ubt_softc {int /*<<< orphan*/  sc_ng_mtx; int /*<<< orphan*/  sc_if_mtx; int /*<<< orphan*/  sc_scoq; int /*<<< orphan*/  sc_aclq; int /*<<< orphan*/  sc_cmdq; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_task; int /*<<< orphan*/ * sc_node; } ;
typedef  int /*<<< orphan*/ * node_p ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  NG_BT_MBUFQ_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_REALLY_DIE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UBT_NG_LOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_NG_UNLOCK (struct ubt_softc*) ; 
 int /*<<< orphan*/  UBT_N_TRANSFER ; 
 struct ubt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ubt_detach(device_t dev)
{
	struct ubt_softc	*sc = device_get_softc(dev);
	node_p			node = sc->sc_node;

	/* Destroy Netgraph node */
	if (node != NULL) {
		sc->sc_node = NULL;
		NG_NODE_REALLY_DIE(node);
		ng_rmnode_self(node);
	}

	/* Make sure ubt_task in gone */
	taskqueue_drain(taskqueue_swi, &sc->sc_task);

	/* Free USB transfers, if any */
	usbd_transfer_unsetup(sc->sc_xfer, UBT_N_TRANSFER);

	/* Destroy queues */
	UBT_NG_LOCK(sc);
	NG_BT_MBUFQ_DESTROY(&sc->sc_cmdq);
	NG_BT_MBUFQ_DESTROY(&sc->sc_aclq);
	NG_BT_MBUFQ_DESTROY(&sc->sc_scoq);
	UBT_NG_UNLOCK(sc);

	mtx_destroy(&sc->sc_if_mtx);
	mtx_destroy(&sc->sc_ng_mtx);

	return (0);
}