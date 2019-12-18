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
typedef  int uint32_t ;
struct dwc_hdmi_softc {int /*<<< orphan*/  sc_mode_hook; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_EVENT_CONNECTED ; 
 int /*<<< orphan*/  HDMI_IH_PHY_STAT0 ; 
 int HDMI_IH_PHY_STAT0_HPD ; 
 int RD1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_event ; 

__attribute__((used)) static void
dwc_hdmi_detect_cable(void *arg)
{
	struct dwc_hdmi_softc *sc;
	uint32_t stat;

	sc = arg;

	stat = RD1(sc, HDMI_IH_PHY_STAT0);
	if ((stat & HDMI_IH_PHY_STAT0_HPD) != 0) {
		EVENTHANDLER_INVOKE(hdmi_event, sc->sc_dev,
		    HDMI_EVENT_CONNECTED);
	}

	/* Finished with the interrupt hook */
	config_intrhook_disestablish(&sc->sc_mode_hook);
}