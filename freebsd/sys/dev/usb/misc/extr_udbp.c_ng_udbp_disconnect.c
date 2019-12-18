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
struct udbp_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_hook; int /*<<< orphan*/ * sc_bulk_in_buffer; int /*<<< orphan*/  sc_xmitq_hipri; int /*<<< orphan*/  sc_xmitq; int /*<<< orphan*/ * sc_xfer; } ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_BT_MBUFQ_DRAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_NODE_NUMHOOKS (int /*<<< orphan*/ ) ; 
 struct udbp_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 size_t UDBP_T_RD ; 
 size_t UDBP_T_RD_CS ; 
 size_t UDBP_T_WR ; 
 size_t UDBP_T_WR_CS ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_udbp_disconnect(hook_p hook)
{
	struct udbp_softc *sc = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));
	int error = 0;

	if (sc != NULL) {

		mtx_lock(&sc->sc_mtx);

		if (hook != sc->sc_hook) {
			error = EINVAL;
		} else {

			/* stop bulk-in transfer */
			usbd_transfer_stop(sc->sc_xfer[UDBP_T_RD_CS]);
			usbd_transfer_stop(sc->sc_xfer[UDBP_T_RD]);

			/* stop bulk-out transfer */
			usbd_transfer_stop(sc->sc_xfer[UDBP_T_WR_CS]);
			usbd_transfer_stop(sc->sc_xfer[UDBP_T_WR]);

			/* cleanup queues */
			NG_BT_MBUFQ_DRAIN(&sc->sc_xmitq);
			NG_BT_MBUFQ_DRAIN(&sc->sc_xmitq_hipri);

			if (sc->sc_bulk_in_buffer) {
				m_freem(sc->sc_bulk_in_buffer);
				sc->sc_bulk_in_buffer = NULL;
			}
			sc->sc_hook = NULL;
		}

		mtx_unlock(&sc->sc_mtx);
	}
	if ((NG_NODE_NUMHOOKS(NG_HOOK_NODE(hook)) == 0)
	    && (NG_NODE_IS_VALID(NG_HOOK_NODE(hook))))
		ng_rmnode_self(NG_HOOK_NODE(hook));

	return (error);
}