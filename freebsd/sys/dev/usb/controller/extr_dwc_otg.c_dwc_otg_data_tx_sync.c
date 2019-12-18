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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct dwc_otg_td {scalar_t__ ep_no; } ;
struct dwc_otg_softc {int sc_last_rx_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOTG_DIEPTSIZ (scalar_t__) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ DXEPTSIZ_GET_NPKT (int) ; 
 scalar_t__ GRXSTSRD_CHNUM_GET (int) ; 
 int GRXSTSRD_PKTSTS_MASK ; 
 int GRXSTSRD_STP_COMPLETE ; 
 int GRXSTSRD_STP_DATA ; 
 int /*<<< orphan*/  dwc_otg_common_rx_ack (struct dwc_otg_softc*) ; 

__attribute__((used)) static uint8_t
dwc_otg_data_tx_sync(struct dwc_otg_softc *sc, struct dwc_otg_td *td)
{
	uint32_t temp;

	/*
	 * If all packets are transferred we are complete:
	 */
	temp = DWC_OTG_READ_4(sc, DOTG_DIEPTSIZ(td->ep_no));

	/* check that all packets have been transferred */
	if (DXEPTSIZ_GET_NPKT(temp) != 0) {
		DPRINTFN(5, "busy ep=%d\n", td->ep_no);
		goto not_complete;
	}
	return (0);

not_complete:

	/* we only want to know if there is a SETUP packet or free IN packet */

	temp = sc->sc_last_rx_status;

	if ((td->ep_no == 0) && (temp != 0) &&
	    (GRXSTSRD_CHNUM_GET(temp) == 0)) {

		if ((temp & GRXSTSRD_PKTSTS_MASK) ==
		    GRXSTSRD_STP_DATA ||
		    (temp & GRXSTSRD_PKTSTS_MASK) ==
		    GRXSTSRD_STP_COMPLETE) {
			DPRINTFN(5, "faking complete\n");
			/*
			 * Race condition: We are complete!
			 */
			return (0);
		} else {
			/* dump data - wrong direction */
			dwc_otg_common_rx_ack(sc);
		}
	}
	return (1);			/* not complete */
}