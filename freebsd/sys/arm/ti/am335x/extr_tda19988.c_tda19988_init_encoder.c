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
typedef  int uint16_t ;
struct videomode {int htotal; int vtotal; int hsync_end; int hdisplay; int hsync_start; int flags; int hskew; int vsync_start; int vdisplay; int vsync_end; int dot_clock; } ;
struct tda19988_softc {scalar_t__ sc_version; } ;

/* Variables and functions */
 int ENC_CNTRL_DVI_MODE ; 
 int /*<<< orphan*/  HDCP_TX33_HDMI ; 
 int HVF_CNTRL_0_INTPOL_BYPASS ; 
 int HVF_CNTRL_0_PREFIL_NONE ; 
 int HVF_CNTRL_1_VQR_FULL ; 
 int /*<<< orphan*/  MAT_CONTRL_MAT_BP ; 
 int /*<<< orphan*/  PLL_SERIAL_1_SRL_MAN_IP ; 
 int PLL_SERIAL_2_SRL_NOSC (int) ; 
 int PLL_SERIAL_2_SRL_PR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLL_SERIAL_3_SRL_CCIR ; 
 int /*<<< orphan*/  PLL_SERIAL_3_SRL_DE ; 
 int SEL_CLK_ENA_SC_CLK ; 
 int SEL_CLK_SEL_CLK1 ; 
 int SEL_CLK_SEL_VRF_CLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBG_CNTRL_0_SYNC_MTHD ; 
 int /*<<< orphan*/  TBG_CNTRL_0_SYNC_ONCE ; 
 int /*<<< orphan*/  TBG_CNTRL_1_DWIN_DIS ; 
 int TBG_CNTRL_1_H_TGL ; 
 int TBG_CNTRL_1_TGL_EN ; 
 int TBG_CNTRL_1_V_TGL ; 
 scalar_t__ TDA19988 ; 
 int /*<<< orphan*/  TDA_ANA_GENERAL ; 
 int /*<<< orphan*/  TDA_DE_START_MSB ; 
 int /*<<< orphan*/  TDA_DE_STOP_MSB ; 
 int /*<<< orphan*/  TDA_ENABLE_SPACE ; 
 int /*<<< orphan*/  TDA_ENC_CNTRL ; 
 int /*<<< orphan*/  TDA_HDCP_TX33 ; 
 int /*<<< orphan*/  TDA_HS_PIX_START_MSB ; 
 int /*<<< orphan*/  TDA_HS_PIX_STOP_MSB ; 
 int /*<<< orphan*/  TDA_HVF_CNTRL_0 ; 
 int /*<<< orphan*/  TDA_HVF_CNTRL_1 ; 
 int /*<<< orphan*/  TDA_MAT_CONTRL ; 
 int /*<<< orphan*/  TDA_NLINE_MSB ; 
 int /*<<< orphan*/  TDA_NPIX_MSB ; 
 int /*<<< orphan*/  TDA_PLL_SERIAL_1 ; 
 int /*<<< orphan*/  TDA_PLL_SERIAL_2 ; 
 int /*<<< orphan*/  TDA_PLL_SERIAL_3 ; 
 int /*<<< orphan*/  TDA_REFLINE_MSB ; 
 int /*<<< orphan*/  TDA_REFPIX_MSB ; 
 int /*<<< orphan*/  TDA_RPT_CNTRL ; 
 int /*<<< orphan*/  TDA_SEL_CLK ; 
 int /*<<< orphan*/  TDA_SERIALIZER ; 
 int /*<<< orphan*/  TDA_TBG_CNTRL_0 ; 
 int /*<<< orphan*/  TDA_TBG_CNTRL_1 ; 
 int /*<<< orphan*/  TDA_VIDFORMAT ; 
 int /*<<< orphan*/  TDA_VIP_CNTRL_3 ; 
 int /*<<< orphan*/  TDA_VIP_CNTRL_4 ; 
 int /*<<< orphan*/  TDA_VIP_CNTRL_5 ; 
 int /*<<< orphan*/  TDA_VS_LINE_END_1_MSB ; 
 int /*<<< orphan*/  TDA_VS_LINE_END_2_MSB ; 
 int /*<<< orphan*/  TDA_VS_LINE_STRT_1_MSB ; 
 int /*<<< orphan*/  TDA_VS_LINE_STRT_2_MSB ; 
 int /*<<< orphan*/  TDA_VS_PIX_END_1_MSB ; 
 int /*<<< orphan*/  TDA_VS_PIX_END_2_MSB ; 
 int /*<<< orphan*/  TDA_VS_PIX_STRT_1_MSB ; 
 int /*<<< orphan*/  TDA_VS_PIX_STRT_2_MSB ; 
 int /*<<< orphan*/  TDA_VWIN_END_1_MSB ; 
 int /*<<< orphan*/  TDA_VWIN_END_2_MSB ; 
 int /*<<< orphan*/  TDA_VWIN_START_1_MSB ; 
 int /*<<< orphan*/  TDA_VWIN_START_2_MSB ; 
 int VID_HSKEW ; 
 int VID_INTERLACE ; 
 int VID_NHSYNC ; 
 int VID_NVSYNC ; 
 int VIP_CNTRL_3_H_TGL ; 
 int VIP_CNTRL_3_SYNC_HS ; 
 int VIP_CNTRL_3_V_TGL ; 
 int VIP_CNTRL_4_BLANKIT_NDE ; 
 int VIP_CNTRL_4_BLC_NONE ; 
 int VIP_CNTRL_5_SP_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda19988_reg_clear (struct tda19988_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda19988_reg_set (struct tda19988_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda19988_reg_write (struct tda19988_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda19988_reg_write2 (struct tda19988_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tda19988_init_encoder(struct tda19988_softc *sc, const struct videomode *mode)
{
	uint16_t ref_pix, ref_line, n_pix, n_line;
	uint16_t hs_pix_start, hs_pix_stop;
	uint16_t vs1_pix_start, vs1_pix_stop;
	uint16_t vs1_line_start, vs1_line_end;
	uint16_t vs2_pix_start, vs2_pix_stop;
	uint16_t vs2_line_start, vs2_line_end;
	uint16_t vwin1_line_start, vwin1_line_end;
	uint16_t vwin2_line_start, vwin2_line_end;
	uint16_t de_start, de_stop;
	uint8_t reg, div;

	n_pix = mode->htotal;
	n_line = mode->vtotal;

	hs_pix_stop = mode->hsync_end - mode->hdisplay;
	hs_pix_start = mode->hsync_start - mode->hdisplay;

	de_stop = mode->htotal;
	de_start = mode->htotal - mode->hdisplay;
	ref_pix = hs_pix_start + 3;

	if (mode->flags & VID_HSKEW)
		ref_pix += mode->hskew;

	if ((mode->flags & VID_INTERLACE) == 0) {
		ref_line = 1 + mode->vsync_start - mode->vdisplay;
		vwin1_line_start = mode->vtotal - mode->vdisplay - 1;
		vwin1_line_end = vwin1_line_start + mode->vdisplay;

		vs1_pix_start = vs1_pix_stop = hs_pix_start;
		vs1_line_start = mode->vsync_start - mode->vdisplay;
		vs1_line_end = vs1_line_start + mode->vsync_end - mode->vsync_start;

		vwin2_line_start = vwin2_line_end = 0;
		vs2_pix_start = vs2_pix_stop = 0;
		vs2_line_start = vs2_line_end = 0;
	} else {
		ref_line = 1 + (mode->vsync_start - mode->vdisplay)/2;
		vwin1_line_start = (mode->vtotal - mode->vdisplay)/2;
		vwin1_line_end = vwin1_line_start + mode->vdisplay/2;

		vs1_pix_start = vs1_pix_stop = hs_pix_start;
		vs1_line_start = (mode->vsync_start - mode->vdisplay)/2;
		vs1_line_end = vs1_line_start + (mode->vsync_end - mode->vsync_start)/2;

		vwin2_line_start = vwin1_line_start + mode->vtotal/2;
		vwin2_line_end = vwin2_line_start + mode->vdisplay/2;

		vs2_pix_start = vs2_pix_stop = hs_pix_start + mode->htotal/2;
		vs2_line_start = vs1_line_start + mode->vtotal/2 ;
		vs2_line_end = vs2_line_start + (mode->vsync_end - mode->vsync_start)/2;
	}

	div = 148500 / mode->dot_clock;
	if (div != 0) {
		div--;
		if (div > 3)
			div = 3;
	}

	/* set HDMI HDCP mode off */
	tda19988_reg_set(sc, TDA_TBG_CNTRL_1, TBG_CNTRL_1_DWIN_DIS);
	tda19988_reg_clear(sc, TDA_HDCP_TX33, HDCP_TX33_HDMI);
	tda19988_reg_write(sc, TDA_ENC_CNTRL, ENC_CNTRL_DVI_MODE);

	/* no pre-filter or interpolator */
	tda19988_reg_write(sc, TDA_HVF_CNTRL_0,
	    HVF_CNTRL_0_INTPOL_BYPASS | HVF_CNTRL_0_PREFIL_NONE);
	tda19988_reg_write(sc, TDA_VIP_CNTRL_5, VIP_CNTRL_5_SP_CNT(0));
	tda19988_reg_write(sc, TDA_VIP_CNTRL_4,
	    VIP_CNTRL_4_BLANKIT_NDE | VIP_CNTRL_4_BLC_NONE);

	tda19988_reg_clear(sc, TDA_PLL_SERIAL_3, PLL_SERIAL_3_SRL_CCIR);
	tda19988_reg_clear(sc, TDA_PLL_SERIAL_1, PLL_SERIAL_1_SRL_MAN_IP);
	tda19988_reg_clear(sc, TDA_PLL_SERIAL_3, PLL_SERIAL_3_SRL_DE);
	tda19988_reg_write(sc, TDA_SERIALIZER, 0);
	tda19988_reg_write(sc, TDA_HVF_CNTRL_1, HVF_CNTRL_1_VQR_FULL);

	tda19988_reg_write(sc, TDA_RPT_CNTRL, 0);
	tda19988_reg_write(sc, TDA_SEL_CLK, SEL_CLK_SEL_VRF_CLK(0) |
			SEL_CLK_SEL_CLK1 | SEL_CLK_ENA_SC_CLK);

	tda19988_reg_write(sc, TDA_PLL_SERIAL_2, PLL_SERIAL_2_SRL_NOSC(div) |
			PLL_SERIAL_2_SRL_PR(0));

	tda19988_reg_set(sc, TDA_MAT_CONTRL, MAT_CONTRL_MAT_BP);

	tda19988_reg_write(sc, TDA_ANA_GENERAL, 0x09);

	tda19988_reg_clear(sc, TDA_TBG_CNTRL_0, TBG_CNTRL_0_SYNC_MTHD);

	/*
	 * Sync on rising HSYNC/VSYNC
	 */
	reg = VIP_CNTRL_3_SYNC_HS;
	if (mode->flags & VID_NHSYNC)
		reg |= VIP_CNTRL_3_H_TGL;
	if (mode->flags & VID_NVSYNC)
		reg |= VIP_CNTRL_3_V_TGL;
	tda19988_reg_write(sc, TDA_VIP_CNTRL_3, reg);

	reg = TBG_CNTRL_1_TGL_EN;
	if (mode->flags & VID_NHSYNC)
		reg |= TBG_CNTRL_1_H_TGL;
	if (mode->flags & VID_NVSYNC)
		reg |= TBG_CNTRL_1_V_TGL;
	tda19988_reg_write(sc, TDA_TBG_CNTRL_1, reg);

	/* Program timing */
	tda19988_reg_write(sc, TDA_VIDFORMAT, 0x00);

	tda19988_reg_write2(sc, TDA_REFPIX_MSB, ref_pix);
	tda19988_reg_write2(sc, TDA_REFLINE_MSB, ref_line);
	tda19988_reg_write2(sc, TDA_NPIX_MSB, n_pix);
	tda19988_reg_write2(sc, TDA_NLINE_MSB, n_line);

	tda19988_reg_write2(sc, TDA_VS_LINE_STRT_1_MSB, vs1_line_start);
	tda19988_reg_write2(sc, TDA_VS_PIX_STRT_1_MSB, vs1_pix_start);
	tda19988_reg_write2(sc, TDA_VS_LINE_END_1_MSB, vs1_line_end);
	tda19988_reg_write2(sc, TDA_VS_PIX_END_1_MSB, vs1_pix_stop);
	tda19988_reg_write2(sc, TDA_VS_LINE_STRT_2_MSB, vs2_line_start);
	tda19988_reg_write2(sc, TDA_VS_PIX_STRT_2_MSB, vs2_pix_start);
	tda19988_reg_write2(sc, TDA_VS_LINE_END_2_MSB, vs2_line_end);
	tda19988_reg_write2(sc, TDA_VS_PIX_END_2_MSB, vs2_pix_stop);
	tda19988_reg_write2(sc, TDA_HS_PIX_START_MSB, hs_pix_start);
	tda19988_reg_write2(sc, TDA_HS_PIX_STOP_MSB, hs_pix_stop);
	tda19988_reg_write2(sc, TDA_VWIN_START_1_MSB, vwin1_line_start);
	tda19988_reg_write2(sc, TDA_VWIN_END_1_MSB, vwin1_line_end);
	tda19988_reg_write2(sc, TDA_VWIN_START_2_MSB, vwin2_line_start);
	tda19988_reg_write2(sc, TDA_VWIN_END_2_MSB, vwin2_line_end);
	tda19988_reg_write2(sc, TDA_DE_START_MSB, de_start);
	tda19988_reg_write2(sc, TDA_DE_STOP_MSB, de_stop);

	if (sc->sc_version == TDA19988)
		tda19988_reg_write(sc, TDA_ENABLE_SPACE, 0x00);

	/* must be last register set */
	tda19988_reg_clear(sc, TDA_TBG_CNTRL_0, TBG_CNTRL_0_SYNC_ONCE);
}