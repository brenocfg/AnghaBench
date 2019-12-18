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
typedef  int /*<<< orphan*/  uint8_t ;
struct dwc_hdmi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_FC_INVIDCONF ; 
 int /*<<< orphan*/  HDMI_MC_SWRSTZ ; 
 scalar_t__ HDMI_MC_SWRSTZ_TMDSSWRST_REQ ; 
 int /*<<< orphan*/  RD1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwc_hdmi_clear_overflow(struct dwc_hdmi_softc *sc)
{
	int count;
	uint8_t val;

	/* TMDS software reset */
	WR1(sc, HDMI_MC_SWRSTZ, (uint8_t)~HDMI_MC_SWRSTZ_TMDSSWRST_REQ);

	val = RD1(sc, HDMI_FC_INVIDCONF);

	for (count = 0 ; count < 4 ; count++)
		WR1(sc, HDMI_FC_INVIDCONF, val);
}