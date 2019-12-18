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
struct udbp_softc {int sc_flags; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; } ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HOOK_FORCE_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_PEER (int /*<<< orphan*/ ) ; 
 struct udbp_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int UDBP_FLAG_READ_STALL ; 
 int UDBP_FLAG_WRITE_STALL ; 
 size_t UDBP_T_RD ; 
 size_t UDBP_T_WR ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_udbp_connect(hook_p hook)
{
	struct udbp_softc *sc = NG_NODE_PRIVATE(NG_HOOK_NODE(hook));

	/* probably not at splnet, force outward queueing */
	NG_HOOK_FORCE_QUEUE(NG_HOOK_PEER(hook));

	mtx_lock(&sc->sc_mtx);

	sc->sc_flags |= (UDBP_FLAG_READ_STALL |
	    UDBP_FLAG_WRITE_STALL);

	/* start bulk-in transfer */
	usbd_transfer_start(sc->sc_xfer[UDBP_T_RD]);

	/* start bulk-out transfer */
	usbd_transfer_start(sc->sc_xfer[UDBP_T_WR]);

	mtx_unlock(&sc->sc_mtx);

	return (0);
}