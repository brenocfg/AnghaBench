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
struct panel_info {int h_back_porch; int h_pulse_width; int h_front_porch; int v_back_porch; int v_pulse_width; int v_front_porch; int clk_div; } ;
struct TYPE_2__ {int fb_height; int fb_width; int fb_pbase; } ;
struct dcu_softc {TYPE_1__ sc_info; struct panel_info* panel; } ;

/* Variables and functions */
 int BPP24 ; 
 int BPP_SHIFT ; 
 int BP_H_SHIFT ; 
 int BP_V_SHIFT ; 
 int /*<<< orphan*/  DCU_BGND ; 
 int /*<<< orphan*/  DCU_CTRLDESCLn_1 (int) ; 
 int /*<<< orphan*/  DCU_CTRLDESCLn_2 (int) ; 
 int /*<<< orphan*/  DCU_CTRLDESCLn_3 (int) ; 
 int /*<<< orphan*/  DCU_CTRLDESCLn_4 (int) ; 
 int /*<<< orphan*/  DCU_CTRLDESCLn_5 (int) ; 
 int /*<<< orphan*/  DCU_CTRLDESCLn_6 (int) ; 
 int /*<<< orphan*/  DCU_CTRLDESCLn_7 (int) ; 
 int /*<<< orphan*/  DCU_CTRLDESCLn_8 (int) ; 
 int /*<<< orphan*/  DCU_CTRLDESCLn_9 (int) ; 
 int /*<<< orphan*/  DCU_DCU_MODE ; 
 int /*<<< orphan*/  DCU_DISP_SIZE ; 
 int /*<<< orphan*/  DCU_DIV_RATIO ; 
 int /*<<< orphan*/  DCU_HSYN_PARA ; 
 int /*<<< orphan*/  DCU_INT_MASK ; 
 int DCU_MODE_M ; 
 int DCU_MODE_NORMAL ; 
 int DCU_MODE_S ; 
 int /*<<< orphan*/  DCU_SYNPOL ; 
 int /*<<< orphan*/  DCU_THRESHOLD ; 
 int /*<<< orphan*/  DCU_UPDATE_MODE ; 
 int /*<<< orphan*/  DCU_VSYN_PARA ; 
 int DELTA_Y_S ; 
 int EN_LAYER ; 
 int FP_H_SHIFT ; 
 int FP_V_SHIFT ; 
 int INV_HS ; 
 int INV_VS ; 
 int LS_BF_VS_SHIFT ; 
 int NUM_LAYERS ; 
 int OUT_BUF_HIGH_SHIFT ; 
 int OUT_BUF_LOW_SHIFT ; 
 int PW_H_SHIFT ; 
 int PW_V_SHIFT ; 
 int RASTER_EN ; 
 int READ4 (struct dcu_softc*,int /*<<< orphan*/ ) ; 
 int READREG ; 
 int TRANS_SHIFT ; 
 int /*<<< orphan*/  WRITE4 (struct dcu_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dcu_init(struct dcu_softc *sc)
{
	struct panel_info *panel;
	int reg;
	int i;

	panel = sc->panel;

	/* Configure DCU */
	reg = ((sc->sc_info.fb_height) << DELTA_Y_S);
	reg |= (sc->sc_info.fb_width / 16);
	WRITE4(sc, DCU_DISP_SIZE, reg);

	reg = (panel->h_back_porch << BP_H_SHIFT);
	reg |= (panel->h_pulse_width << PW_H_SHIFT);
	reg |= (panel->h_front_porch << FP_H_SHIFT);
	WRITE4(sc, DCU_HSYN_PARA, reg);

	reg = (panel->v_back_porch << BP_V_SHIFT);
	reg |= (panel->v_pulse_width << PW_V_SHIFT);
	reg |= (panel->v_front_porch << FP_V_SHIFT);
	WRITE4(sc, DCU_VSYN_PARA, reg);

	WRITE4(sc, DCU_BGND, 0);
	WRITE4(sc, DCU_DIV_RATIO, panel->clk_div);

	reg = (INV_VS | INV_HS);
	WRITE4(sc, DCU_SYNPOL, reg);

	/* TODO: export to panel info */
	reg = (0x3 << LS_BF_VS_SHIFT);
	reg |= (0x78 << OUT_BUF_HIGH_SHIFT);
	reg |= (0 << OUT_BUF_LOW_SHIFT);
	WRITE4(sc, DCU_THRESHOLD, reg);

	/* Mask all the interrupts */
	WRITE4(sc, DCU_INT_MASK, 0xffffffff);

	/* Reset all layers */
	for (i = 0; i < NUM_LAYERS; i++) {
		WRITE4(sc, DCU_CTRLDESCLn_1(i), 0x0);
		WRITE4(sc, DCU_CTRLDESCLn_2(i), 0x0);
		WRITE4(sc, DCU_CTRLDESCLn_3(i), 0x0);
		WRITE4(sc, DCU_CTRLDESCLn_4(i), 0x0);
		WRITE4(sc, DCU_CTRLDESCLn_5(i), 0x0);
		WRITE4(sc, DCU_CTRLDESCLn_6(i), 0x0);
		WRITE4(sc, DCU_CTRLDESCLn_7(i), 0x0);
		WRITE4(sc, DCU_CTRLDESCLn_8(i), 0x0);
		WRITE4(sc, DCU_CTRLDESCLn_9(i), 0x0);
	}

	/* Setup first layer */
	reg = (sc->sc_info.fb_width | (sc->sc_info.fb_height << 16));
	WRITE4(sc, DCU_CTRLDESCLn_1(0), reg);
	WRITE4(sc, DCU_CTRLDESCLn_2(0), 0x0);
	WRITE4(sc, DCU_CTRLDESCLn_3(0), sc->sc_info.fb_pbase);
	reg = (BPP24 << BPP_SHIFT);
	reg |= EN_LAYER;
	reg |= (0xFF << TRANS_SHIFT); /* completely opaque */
	WRITE4(sc, DCU_CTRLDESCLn_4(0), reg);
	WRITE4(sc, DCU_CTRLDESCLn_5(0), 0xffffff);
	WRITE4(sc, DCU_CTRLDESCLn_6(0), 0x0);
	WRITE4(sc, DCU_CTRLDESCLn_7(0), 0x0);
	WRITE4(sc, DCU_CTRLDESCLn_8(0), 0x0);
	WRITE4(sc, DCU_CTRLDESCLn_9(0), 0x0);

	/* Enable DCU in normal mode */
	reg = READ4(sc, DCU_DCU_MODE);
	reg &= ~(DCU_MODE_M << DCU_MODE_S);
	reg |= (DCU_MODE_NORMAL << DCU_MODE_S);
	reg |= (RASTER_EN);
	WRITE4(sc, DCU_DCU_MODE, reg);
	WRITE4(sc, DCU_UPDATE_MODE, READREG);

	return (0);
}