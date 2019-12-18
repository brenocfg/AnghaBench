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
struct dwc_hdmi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_IH_I2CMPHY_STAT0 ; 
 int HDMI_IH_I2CMPHY_STAT0_DONE ; 
 int HDMI_IH_I2CMPHY_STAT0_ERROR ; 
 int RD1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static void
dwc_hdmi_phy_wait_i2c_done(struct dwc_hdmi_softc *sc, int msec)
{
	uint8_t val;

	val = RD1(sc, HDMI_IH_I2CMPHY_STAT0) &
	    (HDMI_IH_I2CMPHY_STAT0_DONE | HDMI_IH_I2CMPHY_STAT0_ERROR);
	while (val == 0) {
		pause("HDMI_PHY", hz/100);
		msec -= 10;
		if (msec <= 0)
			return;
		val = RD1(sc, HDMI_IH_I2CMPHY_STAT0) &
		    (HDMI_IH_I2CMPHY_STAT0_DONE | HDMI_IH_I2CMPHY_STAT0_ERROR);
	}
}