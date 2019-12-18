#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct dwc_hdmi_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct dwc_hdmi_softc {int /*<<< orphan*/ * sc_edid; TYPE_1__ sc_mode_hook; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_edid_len; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDID_LENGTH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HDMI_DESIGN_ID ; 
 int /*<<< orphan*/  HDMI_IH_PHY_STAT0 ; 
 int /*<<< orphan*/  HDMI_IH_PHY_STAT0_HPD ; 
 int /*<<< orphan*/  HDMI_PHY_POL0 ; 
 int /*<<< orphan*/  HDMI_PHY_POL0_HPD ; 
 int /*<<< orphan*/  HDMI_PRODUCT_ID0 ; 
 int /*<<< orphan*/  HDMI_PRODUCT_ID1 ; 
 int /*<<< orphan*/  HDMI_REVISION_ID ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RD1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 struct dwc_hdmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_hdmi_detect_cable ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
dwc_hdmi_init(device_t dev)
{
	struct dwc_hdmi_softc *sc;
	int err;

	sc = device_get_softc(dev);
	err = 0;

	sc->sc_edid = malloc(EDID_LENGTH, M_DEVBUF, M_WAITOK | M_ZERO);
	sc->sc_edid_len = EDID_LENGTH;

	device_printf(sc->sc_dev, "HDMI controller %02x:%02x:%02x:%02x\n",
	    RD1(sc, HDMI_DESIGN_ID), RD1(sc, HDMI_REVISION_ID),
	    RD1(sc, HDMI_PRODUCT_ID0), RD1(sc, HDMI_PRODUCT_ID1));

	WR1(sc, HDMI_PHY_POL0, HDMI_PHY_POL0_HPD);
	WR1(sc, HDMI_IH_PHY_STAT0, HDMI_IH_PHY_STAT0_HPD);

	sc->sc_mode_hook.ich_func = dwc_hdmi_detect_cable;
	sc->sc_mode_hook.ich_arg = sc;
	if (config_intrhook_establish(&sc->sc_mode_hook) != 0) {
		err = ENOMEM;
		goto out;
	}

out:

	if (err != 0) {
		free(sc->sc_edid, M_DEVBUF);
		sc->sc_edid = NULL;
	}

	return (err);
}