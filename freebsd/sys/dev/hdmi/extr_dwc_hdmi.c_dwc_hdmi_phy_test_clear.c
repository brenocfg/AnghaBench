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
typedef  unsigned char uint8_t ;
struct dwc_hdmi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_PHY_TST0 ; 
 unsigned char HDMI_PHY_TST0_TSTCLR_MASK ; 
 unsigned char HDMI_PHY_TST0_TSTCLR_OFFSET ; 
 unsigned char RD1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static inline void
dwc_hdmi_phy_test_clear(struct dwc_hdmi_softc *sc, unsigned char bit)
{
	uint8_t val;

	val = RD1(sc, HDMI_PHY_TST0);
	val &= ~HDMI_PHY_TST0_TSTCLR_MASK;
	val |= (bit << HDMI_PHY_TST0_TSTCLR_OFFSET) &
		HDMI_PHY_TST0_TSTCLR_MASK;
	WR1(sc, HDMI_PHY_TST0, val);
}