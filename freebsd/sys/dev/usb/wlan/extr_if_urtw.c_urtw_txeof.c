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
struct usb_xfer {int dummy; } ;
struct urtw_softc {scalar_t__ sc_txtimer; } ;
struct urtw_data {int /*<<< orphan*/ * ni; int /*<<< orphan*/ * m; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_ASSERT_LOCKED (struct urtw_softc*) ; 
 int /*<<< orphan*/  ieee80211_tx_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct urtw_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
urtw_txeof(struct usb_xfer *xfer, struct urtw_data *data)
{
	struct urtw_softc *sc = usbd_xfer_softc(xfer);

	URTW_ASSERT_LOCKED(sc);

	if (data->m) {
		/* XXX status? */
		ieee80211_tx_complete(data->ni, data->m, 0);
		data->m = NULL;
		data->ni = NULL;
	}
	sc->sc_txtimer = 0;
}