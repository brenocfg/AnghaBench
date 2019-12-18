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
typedef  size_t uint8_t ;
struct dwc_otg_td {size_t max_packet_count; scalar_t__* channel; } ;
struct dwc_otg_softc {scalar_t__ sc_last_rx_status; } ;

/* Variables and functions */
 scalar_t__ DWC_OTG_MAX_CHANNELS ; 
 scalar_t__ GRXSTSRD_CHNUM_GET (scalar_t__) ; 
 int /*<<< orphan*/  dwc_otg_common_rx_ack (struct dwc_otg_softc*) ; 

__attribute__((used)) static void
dwc_otg_host_dump_rx(struct dwc_otg_softc *sc, struct dwc_otg_td *td)
{
	uint8_t x;
	/* dump any pending messages */
	if (sc->sc_last_rx_status == 0)
		return;
	for (x = 0; x != td->max_packet_count; x++) {
		if (td->channel[x] >= DWC_OTG_MAX_CHANNELS ||
		    td->channel[x] != GRXSTSRD_CHNUM_GET(sc->sc_last_rx_status))
			continue;
		dwc_otg_common_rx_ack(sc);
		break;
	}
}