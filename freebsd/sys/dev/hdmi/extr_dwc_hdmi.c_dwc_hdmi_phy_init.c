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
struct dwc_hdmi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc_hdmi_phy_configure (struct dwc_hdmi_softc*) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_enable_power (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_enable_tmds (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_sel_data_en_pol (struct dwc_hdmi_softc*,int) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_sel_interface_control (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwc_hdmi_phy_init(struct dwc_hdmi_softc *sc)
{
	int i;

	/* HDMI Phy spec says to do the phy initialization sequence twice */
	for (i = 0 ; i < 2 ; i++) {
		dwc_hdmi_phy_sel_data_en_pol(sc, 1);
		dwc_hdmi_phy_sel_interface_control(sc, 0);
		dwc_hdmi_phy_enable_tmds(sc, 0);
		dwc_hdmi_phy_enable_power(sc, 0);

		/* Enable CSC */
		dwc_hdmi_phy_configure(sc);
	}
}