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
struct hn_softc {int hn_flags; scalar_t__ hn_rxbuf_gpadl; scalar_t__ hn_chim_gpadl; int /*<<< orphan*/  hn_ifp; int /*<<< orphan*/  hn_prichan; } ;

/* Variables and functions */
 int HN_FLAG_CHIM_REF ; 
 int HN_FLAG_RXBUF_REF ; 
 int HN_FLAG_SYNTH_ATTACHED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ VMBUS_VERSION_WIN10 ; 
 int /*<<< orphan*/  hn_detach_allchans (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_nvs_detach (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_rndis_detach (struct hn_softc*) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int) ; 
 int vmbus_chan_gpadl_disconnect (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vmbus_current_version ; 

__attribute__((used)) static void
hn_synth_detach(struct hn_softc *sc)
{

	KASSERT(sc->hn_flags & HN_FLAG_SYNTH_ATTACHED,
	    ("synthetic parts were not attached"));

	/* Detach the RNDIS first. */
	hn_rndis_detach(sc);

	/* Detach NVS. */
	hn_nvs_detach(sc);

	/* Detach all of the channels. */
	hn_detach_allchans(sc);

	if (vmbus_current_version >= VMBUS_VERSION_WIN10 && sc->hn_rxbuf_gpadl != 0) {
		/*
		 * Host is post-Win2016, disconnect RXBUF from primary channel here.
		 */
		int error;

		error = vmbus_chan_gpadl_disconnect(sc->hn_prichan,
		    sc->hn_rxbuf_gpadl);
		if (error) {
			if_printf(sc->hn_ifp,
			    "rxbuf gpadl disconn failed: %d\n", error);
			sc->hn_flags |= HN_FLAG_RXBUF_REF;
		}
		sc->hn_rxbuf_gpadl = 0;
	}

	if (vmbus_current_version >= VMBUS_VERSION_WIN10 && sc->hn_chim_gpadl != 0) {
		/*
		 * Host is post-Win2016, disconnect chimney sending buffer from
		 * primary channel here.
		 */
		int error;

		error = vmbus_chan_gpadl_disconnect(sc->hn_prichan,
		    sc->hn_chim_gpadl);
		if (error) {
			if_printf(sc->hn_ifp,
			    "chim gpadl disconn failed: %d\n", error);
			sc->hn_flags |= HN_FLAG_CHIM_REF;
		}
		sc->hn_chim_gpadl = 0;
	}
	sc->hn_flags &= ~HN_FLAG_SYNTH_ATTACHED;
}