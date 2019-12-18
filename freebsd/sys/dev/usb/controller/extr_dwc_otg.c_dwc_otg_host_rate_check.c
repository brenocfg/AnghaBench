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
struct dwc_otg_td {scalar_t__ ep_type; int tmr_res; int tmr_val; int toggle; scalar_t__ did_nak; scalar_t__ set_toggle; scalar_t__ tt_scheduled; } ;
struct dwc_otg_softc {int sc_last_frame_num; } ;

/* Variables and functions */
 scalar_t__ UE_INTERRUPT ; 
 scalar_t__ UE_ISOCHRONOUS ; 
 int /*<<< orphan*/  dwc_otg_enable_sof_irq (struct dwc_otg_softc*) ; 

__attribute__((used)) static uint8_t
dwc_otg_host_rate_check(struct dwc_otg_softc *sc, struct dwc_otg_td *td)
{
	uint8_t frame_num = (uint8_t)sc->sc_last_frame_num;

	if (td->ep_type == UE_ISOCHRONOUS) {
		/* non TT isochronous traffic */
		if (frame_num & (td->tmr_res - 1))
			goto busy;
		if ((frame_num ^ td->tmr_val) & td->tmr_res)
			goto busy;
		td->tmr_val = td->tmr_res + sc->sc_last_frame_num;
		td->toggle = 0;
		return (0);
	} else if (td->ep_type == UE_INTERRUPT) {
		if (!td->tt_scheduled)
			goto busy;
		td->tt_scheduled = 0;
		return (0);
	} else if (td->did_nak != 0) {
		/* check if we should pause sending queries for 125us */
		if (td->tmr_res == frame_num) {
			/* wait a bit */
			dwc_otg_enable_sof_irq(sc);
			goto busy;
		}
	} else if (td->set_toggle) {
		td->set_toggle = 0;
		td->toggle = 1;
	}
	/* query for data one more time */
	td->tmr_res = frame_num;
	td->did_nak = 0;
	return (0);
busy:
	return (1);
}