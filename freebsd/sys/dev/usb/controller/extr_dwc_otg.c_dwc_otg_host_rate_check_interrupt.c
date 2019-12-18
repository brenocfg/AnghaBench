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
struct dwc_otg_td {int tmr_val; int tmr_res; int toggle; scalar_t__ set_toggle; } ;
struct dwc_otg_softc {int sc_tmr_val; } ;

/* Variables and functions */

__attribute__((used)) static uint8_t
dwc_otg_host_rate_check_interrupt(struct dwc_otg_softc *sc, struct dwc_otg_td *td)
{
	uint8_t delta;

	delta = sc->sc_tmr_val - td->tmr_val;
	if (delta >= 128)
		return (1);	/* busy */

	td->tmr_val = sc->sc_tmr_val + td->tmr_res;

	/* set toggle, if any */
	if (td->set_toggle) {
		td->set_toggle = 0;
		td->toggle = 1;
	}
	return (0);
}