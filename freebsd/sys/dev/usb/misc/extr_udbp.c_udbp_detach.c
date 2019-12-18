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
struct udbp_softc {int /*<<< orphan*/ * sc_bulk_in_buffer; int /*<<< orphan*/  sc_xmitq_hipri; int /*<<< orphan*/  sc_xmitq; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/ * sc_node; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  NG_BT_MBUFQ_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UDBP_T_MAX ; 
 struct udbp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udbp_detach(device_t dev)
{
	struct udbp_softc *sc = device_get_softc(dev);

	/* destroy Netgraph node */

	if (sc->sc_node != NULL) {
		NG_NODE_SET_PRIVATE(sc->sc_node, NULL);
		ng_rmnode_self(sc->sc_node);
		sc->sc_node = NULL;
	}
	/* free USB transfers, if any */

	usbd_transfer_unsetup(sc->sc_xfer, UDBP_T_MAX);

	mtx_destroy(&sc->sc_mtx);

	/* destroy queues */

	NG_BT_MBUFQ_DESTROY(&sc->sc_xmitq);
	NG_BT_MBUFQ_DESTROY(&sc->sc_xmitq_hipri);

	/* extra check */

	if (sc->sc_bulk_in_buffer) {
		m_freem(sc->sc_bulk_in_buffer);
		sc->sc_bulk_in_buffer = NULL;
	}
	return (0);			/* success */
}