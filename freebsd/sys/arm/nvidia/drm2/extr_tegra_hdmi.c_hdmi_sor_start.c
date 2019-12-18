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
struct hdmi_softc {int /*<<< orphan*/  dev; } ;
struct drm_display_mode {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASY_CRCMODE_COMPLETE ; 
 int /*<<< orphan*/  ASY_HEAD_OPMODE_AWAKE ; 
 int /*<<< orphan*/  ASY_OWNER_HEAD0 ; 
 int /*<<< orphan*/  ASY_PROTOCOL_SINGLE_TMDS_A ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_PLL0 ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_PWR ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_STATE0 ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_STATE1 ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_SOR_STATE2 ; 
 int RD4 (struct hdmi_softc*,int /*<<< orphan*/ ) ; 
 int SOR_PLL0_PDBG ; 
 int SOR_PLL0_PULLDOWN ; 
 int SOR_PLL0_PWR ; 
 int SOR_PLL0_VCOPD ; 
 int SOR_PWR_SETTING_NEW ; 
 int SOR_STATE0_UPDATE ; 
 int SOR_STATE1_ASY_HEAD_OPMODE (int /*<<< orphan*/ ) ; 
 int SOR_STATE1_ASY_ORMODE_NORMAL ; 
 int SOR_STATE1_ATTACHED ; 
 int SOR_STATE2_ASY_CRCMODE (int /*<<< orphan*/ ) ; 
 int SOR_STATE2_ASY_HSYNCPOL_NEG ; 
 int SOR_STATE2_ASY_OWNER (int /*<<< orphan*/ ) ; 
 int SOR_STATE2_ASY_PROTOCOL (int /*<<< orphan*/ ) ; 
 int SOR_STATE2_ASY_SUBOWNER (int /*<<< orphan*/ ) ; 
 int SOR_STATE2_ASY_VSYNCPOL_NEG ; 
 int /*<<< orphan*/  SUBOWNER_BOTH ; 
 int /*<<< orphan*/  WR4 (struct hdmi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
hdmi_sor_start(struct hdmi_softc *sc, struct drm_display_mode *mode)
{
	int i;
	uint32_t val;

	/* Enable TMDS macro */
	val = RD4(sc, HDMI_NV_PDISP_SOR_PLL0);
	val &= ~SOR_PLL0_PWR;
	val &= ~SOR_PLL0_VCOPD;
	val &= ~SOR_PLL0_PULLDOWN;
	WR4(sc, HDMI_NV_PDISP_SOR_PLL0, val);
	DELAY(10);

	val = RD4(sc, HDMI_NV_PDISP_SOR_PLL0);
	val &= ~SOR_PLL0_PDBG;
	WR4(sc, HDMI_NV_PDISP_SOR_PLL0, val);

	WR4(sc, HDMI_NV_PDISP_SOR_PWR, SOR_PWR_SETTING_NEW);
	WR4(sc, HDMI_NV_PDISP_SOR_PWR, 0);

	/* Wait until SOR is ready */
	for (i = 1000; i > 0; i--) {
		val = RD4(sc, HDMI_NV_PDISP_SOR_PWR);
		if ((val & SOR_PWR_SETTING_NEW) == 0)
			break;
		DELAY(10);
	}
	if (i <= 0) {
		device_printf(sc->dev, "Timeouted while enabling SOR power.\n");
		return (ETIMEDOUT);
	}

	val = SOR_STATE2_ASY_OWNER(ASY_OWNER_HEAD0) |
	    SOR_STATE2_ASY_SUBOWNER(SUBOWNER_BOTH) |
	    SOR_STATE2_ASY_CRCMODE(ASY_CRCMODE_COMPLETE) |
	    SOR_STATE2_ASY_PROTOCOL(ASY_PROTOCOL_SINGLE_TMDS_A);
	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		val |= SOR_STATE2_ASY_HSYNCPOL_NEG;
	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		val |= SOR_STATE2_ASY_VSYNCPOL_NEG;
	WR4(sc, HDMI_NV_PDISP_SOR_STATE2, val);

	WR4(sc, HDMI_NV_PDISP_SOR_STATE1, SOR_STATE1_ASY_ORMODE_NORMAL |
	    SOR_STATE1_ASY_HEAD_OPMODE(ASY_HEAD_OPMODE_AWAKE));

	WR4(sc, HDMI_NV_PDISP_SOR_STATE0, 0);
	WR4(sc, HDMI_NV_PDISP_SOR_STATE0, SOR_STATE0_UPDATE);

	val = RD4(sc, HDMI_NV_PDISP_SOR_STATE1);
	val |= SOR_STATE1_ATTACHED;
	WR4(sc, HDMI_NV_PDISP_SOR_STATE1, val);

	WR4(sc, HDMI_NV_PDISP_SOR_STATE0, 0);

	return 0;
}