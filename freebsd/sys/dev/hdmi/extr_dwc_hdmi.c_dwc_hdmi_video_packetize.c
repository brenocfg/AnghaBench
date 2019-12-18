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
 int /*<<< orphan*/  HDMI_VP_CONF ; 
 int HDMI_VP_CONF_BYPASS_EN_DISABLE ; 
 int HDMI_VP_CONF_BYPASS_EN_ENABLE ; 
 int HDMI_VP_CONF_BYPASS_EN_MASK ; 
 int HDMI_VP_CONF_BYPASS_SELECT_MASK ; 
 int HDMI_VP_CONF_BYPASS_SELECT_VID_PACKETIZER ; 
 unsigned int HDMI_VP_CONF_OUTPUT_SELECTOR_BYPASS ; 
 int HDMI_VP_CONF_OUTPUT_SELECTOR_MASK ; 
 unsigned int HDMI_VP_CONF_OUTPUT_SELECTOR_PP ; 
 unsigned int HDMI_VP_CONF_OUTPUT_SELECTOR_YCC422 ; 
 int HDMI_VP_CONF_PP_EN_DISABLE ; 
 int HDMI_VP_CONF_PP_EN_ENABLE ; 
 int HDMI_VP_CONF_PP_EN_ENMASK ; 
 int HDMI_VP_CONF_PR_EN_DISABLE ; 
 int HDMI_VP_CONF_PR_EN_MASK ; 
 int HDMI_VP_CONF_YCC422_EN_DISABLE ; 
 int HDMI_VP_CONF_YCC422_EN_ENABLE ; 
 int HDMI_VP_CONF_YCC422_EN_MASK ; 
 int /*<<< orphan*/  HDMI_VP_PR_CD ; 
 unsigned int HDMI_VP_PR_CD_COLOR_DEPTH_MASK ; 
 unsigned int HDMI_VP_PR_CD_COLOR_DEPTH_OFFSET ; 
 int /*<<< orphan*/  HDMI_VP_REMAP ; 
 unsigned int HDMI_VP_REMAP_YCC422_16BIT ; 
 int /*<<< orphan*/  HDMI_VP_STUFF ; 
 int HDMI_VP_STUFF_IDEFAULT_PHASE_MASK ; 
 int HDMI_VP_STUFF_IDEFAULT_PHASE_OFFSET ; 
 int HDMI_VP_STUFF_PP_STUFFING_MASK ; 
 int HDMI_VP_STUFF_PP_STUFFING_STUFFING_MODE ; 
 int HDMI_VP_STUFF_PR_STUFFING_MASK ; 
 int HDMI_VP_STUFF_PR_STUFFING_STUFFING_MODE ; 
 int HDMI_VP_STUFF_YCC422_STUFFING_MASK ; 
 int HDMI_VP_STUFF_YCC422_STUFFING_STUFFING_MODE ; 
 int RD1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dwc_hdmi_video_packetize(struct dwc_hdmi_softc *sc)
{
	unsigned int color_depth = 0;
	unsigned int remap_size = HDMI_VP_REMAP_YCC422_16BIT;
	unsigned int output_select = HDMI_VP_CONF_OUTPUT_SELECTOR_PP;
	uint8_t val;

	output_select = HDMI_VP_CONF_OUTPUT_SELECTOR_BYPASS;
	color_depth = 4;

	/* set the packetizer registers */
	val = ((color_depth << HDMI_VP_PR_CD_COLOR_DEPTH_OFFSET) &
		HDMI_VP_PR_CD_COLOR_DEPTH_MASK);
	WR1(sc, HDMI_VP_PR_CD, val);

	val = RD1(sc, HDMI_VP_STUFF);
	val &= ~HDMI_VP_STUFF_PR_STUFFING_MASK;
	val |= HDMI_VP_STUFF_PR_STUFFING_STUFFING_MODE;
	WR1(sc, HDMI_VP_STUFF, val);

	val = RD1(sc, HDMI_VP_CONF);
	val &= ~(HDMI_VP_CONF_PR_EN_MASK |
		HDMI_VP_CONF_BYPASS_SELECT_MASK);
	val |= HDMI_VP_CONF_PR_EN_DISABLE |
		HDMI_VP_CONF_BYPASS_SELECT_VID_PACKETIZER;
	WR1(sc, HDMI_VP_CONF, val);

	val = RD1(sc, HDMI_VP_STUFF);
	val &= ~HDMI_VP_STUFF_IDEFAULT_PHASE_MASK;
	val |= 1 << HDMI_VP_STUFF_IDEFAULT_PHASE_OFFSET;
	WR1(sc, HDMI_VP_STUFF, val);

	WR1(sc, HDMI_VP_REMAP, remap_size);

	if (output_select == HDMI_VP_CONF_OUTPUT_SELECTOR_PP) {
		val = RD1(sc, HDMI_VP_CONF);
		val &= ~(HDMI_VP_CONF_BYPASS_EN_MASK |
			HDMI_VP_CONF_PP_EN_ENMASK |
			HDMI_VP_CONF_YCC422_EN_MASK);
		val |= HDMI_VP_CONF_BYPASS_EN_DISABLE |
			HDMI_VP_CONF_PP_EN_ENABLE |
			HDMI_VP_CONF_YCC422_EN_DISABLE;
		WR1(sc, HDMI_VP_CONF, val);
	} else if (output_select == HDMI_VP_CONF_OUTPUT_SELECTOR_YCC422) {
		val = RD1(sc, HDMI_VP_CONF);
		val &= ~(HDMI_VP_CONF_BYPASS_EN_MASK |
			HDMI_VP_CONF_PP_EN_ENMASK |
			HDMI_VP_CONF_YCC422_EN_MASK);
		val |= HDMI_VP_CONF_BYPASS_EN_DISABLE |
			HDMI_VP_CONF_PP_EN_DISABLE |
			HDMI_VP_CONF_YCC422_EN_ENABLE;
		WR1(sc, HDMI_VP_CONF, val);
	} else if (output_select == HDMI_VP_CONF_OUTPUT_SELECTOR_BYPASS) {
		val = RD1(sc, HDMI_VP_CONF);
		val &= ~(HDMI_VP_CONF_BYPASS_EN_MASK |
			HDMI_VP_CONF_PP_EN_ENMASK |
			HDMI_VP_CONF_YCC422_EN_MASK);
		val |= HDMI_VP_CONF_BYPASS_EN_ENABLE |
			HDMI_VP_CONF_PP_EN_DISABLE |
			HDMI_VP_CONF_YCC422_EN_DISABLE;
		WR1(sc, HDMI_VP_CONF, val);
	} else {
		return;
	}

	val = RD1(sc, HDMI_VP_STUFF);
	val &= ~(HDMI_VP_STUFF_PP_STUFFING_MASK |
		HDMI_VP_STUFF_YCC422_STUFFING_MASK);
	val |= HDMI_VP_STUFF_PP_STUFFING_STUFFING_MODE |
		HDMI_VP_STUFF_YCC422_STUFFING_STUFFING_MODE;
	WR1(sc, HDMI_VP_STUFF, val);

	val = RD1(sc, HDMI_VP_CONF);
	val &= ~HDMI_VP_CONF_OUTPUT_SELECTOR_MASK;
	val |= output_select;
	WR1(sc, HDMI_VP_CONF, val);
}