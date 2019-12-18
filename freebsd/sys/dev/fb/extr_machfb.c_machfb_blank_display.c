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
typedef  int /*<<< orphan*/  video_adapter_t ;
typedef  int uint32_t ;
struct machfb_softc {int dummy; } ;

/* Variables and functions */
 int CRTC_DISPLAY_DIS ; 
 int CRTC_EN ; 
 int CRTC_EXT_DISP_EN ; 
 int /*<<< orphan*/  CRTC_GEN_CNTL ; 
 int CRTC_HSYNC_DIS ; 
 int CRTC_VSYNC_DIS ; 
#define  V_DISPLAY_BLANK 131 
#define  V_DISPLAY_ON 130 
#define  V_DISPLAY_STAND_BY 129 
#define  V_DISPLAY_SUSPEND 128 
 int regr (struct machfb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (struct machfb_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
machfb_blank_display(video_adapter_t *adp, int mode)
{
	struct machfb_softc *sc;
	uint32_t crtc_gen_cntl;

	sc = (struct machfb_softc *)adp;

	crtc_gen_cntl = (regr(sc, CRTC_GEN_CNTL) | CRTC_EXT_DISP_EN | CRTC_EN) &
	    ~(CRTC_HSYNC_DIS | CRTC_VSYNC_DIS | CRTC_DISPLAY_DIS);
	switch (mode) {
	case V_DISPLAY_ON:
		break;
	case V_DISPLAY_BLANK:
		crtc_gen_cntl |= CRTC_HSYNC_DIS | CRTC_VSYNC_DIS |
		    CRTC_DISPLAY_DIS;
		break;
	case V_DISPLAY_STAND_BY:
		crtc_gen_cntl |= CRTC_HSYNC_DIS | CRTC_DISPLAY_DIS;
		break;
	case V_DISPLAY_SUSPEND:
		crtc_gen_cntl |= CRTC_VSYNC_DIS | CRTC_DISPLAY_DIS;
		break;
	}
	regw(sc, CRTC_GEN_CNTL, crtc_gen_cntl);

	return (0);
}