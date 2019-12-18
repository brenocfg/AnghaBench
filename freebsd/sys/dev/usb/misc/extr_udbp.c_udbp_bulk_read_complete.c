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
struct udbp_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/ * sc_hook; int /*<<< orphan*/  sc_packets_in; struct mbuf* sc_bulk_in_buffer; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ NG_HOOK_NOT_VALID (int /*<<< orphan*/ *) ; 
 struct udbp_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ *,struct mbuf*) ; 
 size_t UDBP_T_RD ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
udbp_bulk_read_complete(node_p node, hook_p hook, void *arg1, int arg2)
{
	struct udbp_softc *sc = NG_NODE_PRIVATE(node);
	struct mbuf *m;
	int error;

	if (sc == NULL) {
		return;
	}
	mtx_lock(&sc->sc_mtx);

	m = sc->sc_bulk_in_buffer;

	if (m) {

		sc->sc_bulk_in_buffer = NULL;

		if ((sc->sc_hook == NULL) ||
		    NG_HOOK_NOT_VALID(sc->sc_hook)) {
			DPRINTF("No upstream hook\n");
			goto done;
		}
		sc->sc_packets_in++;

		NG_SEND_DATA_ONLY(error, sc->sc_hook, m);

		m = NULL;
	}
done:
	if (m) {
		m_freem(m);
	}
	/* start USB bulk-in transfer, if not already started */

	usbd_transfer_start(sc->sc_xfer[UDBP_T_RD]);

	mtx_unlock(&sc->sc_mtx);
}