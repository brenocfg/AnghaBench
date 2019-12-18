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
struct usie_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_if_xfer; int /*<<< orphan*/  sc_if_sync_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  USIE_CNS_ID_STOP ; 
 int /*<<< orphan*/  USIE_CNS_OB_LINK_UPDATE ; 
 int /*<<< orphan*/  USIE_HIP_DOWN ; 
 size_t USIE_IF_RX ; 
 size_t USIE_IF_STATUS ; 
 size_t USIE_IF_TX ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usie_cns_req (struct usie_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usie_if_cmd (struct usie_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usie_if_stop(struct usie_softc *sc)
{
	usb_callout_drain(&sc->sc_if_sync_ch);

	mtx_lock(&sc->sc_mtx);

	/* usie_cns_req() clears IFF_* flags */
	usie_cns_req(sc, USIE_CNS_ID_STOP, USIE_CNS_OB_LINK_UPDATE);

	usbd_transfer_stop(sc->sc_if_xfer[USIE_IF_TX]);
	usbd_transfer_stop(sc->sc_if_xfer[USIE_IF_RX]);
	usbd_transfer_stop(sc->sc_if_xfer[USIE_IF_STATUS]);

	/* shutdown device */
	usie_if_cmd(sc, USIE_HIP_DOWN);

	mtx_unlock(&sc->sc_mtx);
}