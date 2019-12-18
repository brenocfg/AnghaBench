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
 int /*<<< orphan*/  HDMI_TX_BCBDATA0 ; 
 int /*<<< orphan*/  HDMI_TX_BCBDATA1 ; 
 int /*<<< orphan*/  HDMI_TX_GYDATA0 ; 
 int /*<<< orphan*/  HDMI_TX_GYDATA1 ; 
 int /*<<< orphan*/  HDMI_TX_INSTUFFING ; 
 int HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABLE ; 
 int HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABLE ; 
 int HDMI_TX_INSTUFFING_RCRDATA_STUFFING_ENABLE ; 
 int /*<<< orphan*/  HDMI_TX_INVID0 ; 
 int HDMI_TX_INVID0_INTERNAL_DE_GENERATOR_DISABLE ; 
 int HDMI_TX_INVID0_VIDEO_MAPPING_MASK ; 
 int HDMI_TX_INVID0_VIDEO_MAPPING_OFFSET ; 
 int /*<<< orphan*/  HDMI_TX_RCRDATA0 ; 
 int /*<<< orphan*/  HDMI_TX_RCRDATA1 ; 
 int /*<<< orphan*/  WR1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dwc_hdmi_video_sample(struct dwc_hdmi_softc *sc)
{
	int color_format;
	uint8_t val;

	color_format = 0x01;
	val = HDMI_TX_INVID0_INTERNAL_DE_GENERATOR_DISABLE |
		((color_format << HDMI_TX_INVID0_VIDEO_MAPPING_OFFSET) &
		HDMI_TX_INVID0_VIDEO_MAPPING_MASK);
	WR1(sc, HDMI_TX_INVID0, val);

	/* Enable TX stuffing: When DE is inactive, fix the output data to 0 */
	val = HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABLE |
		HDMI_TX_INSTUFFING_RCRDATA_STUFFING_ENABLE |
		HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABLE;
	WR1(sc, HDMI_TX_INSTUFFING, val);
	WR1(sc, HDMI_TX_GYDATA0, 0x0);
	WR1(sc, HDMI_TX_GYDATA1, 0x0);
	WR1(sc, HDMI_TX_RCRDATA0, 0x0);
	WR1(sc, HDMI_TX_RCRDATA1, 0x0);
	WR1(sc, HDMI_TX_BCBDATA0, 0x0);
	WR1(sc, HDMI_TX_BCBDATA1, 0x0);
}