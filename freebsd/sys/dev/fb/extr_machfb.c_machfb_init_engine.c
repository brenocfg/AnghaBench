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
struct machfb_softc {int sc_width; int sc_depth; int sc_height; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_CMP_CLR ; 
 int /*<<< orphan*/  CLR_CMP_CNTL ; 
 int /*<<< orphan*/  CLR_CMP_MASK ; 
 int /*<<< orphan*/  CONTEXT_MASK ; 
 int /*<<< orphan*/  CRTC_INT_CNTL ; 
 int DAC_8BIT_EN ; 
 int /*<<< orphan*/  DAC_CNTL ; 
 int /*<<< orphan*/  DP_BKGD_CLR ; 
 int DP_CHAIN_32BPP ; 
 int DP_CHAIN_8BPP ; 
 int /*<<< orphan*/  DP_CHAIN_MASK ; 
 int /*<<< orphan*/  DP_FRGD_CLR ; 
 int /*<<< orphan*/  DP_MIX ; 
 int /*<<< orphan*/  DP_PIX_WIDTH ; 
 int /*<<< orphan*/  DP_SRC ; 
 int /*<<< orphan*/  DP_WRITE_MASK ; 
 int DST_32BPP ; 
 int DST_8BPP ; 
 int /*<<< orphan*/  DST_BRES_DEC ; 
 int /*<<< orphan*/  DST_BRES_ERR ; 
 int /*<<< orphan*/  DST_BRES_INC ; 
 int /*<<< orphan*/  DST_CNTL ; 
 int /*<<< orphan*/  DST_HEIGHT ; 
 int DST_LAST_PEL ; 
 int /*<<< orphan*/  DST_OFF_PITCH ; 
 int DST_X_LEFT_TO_RIGHT ; 
 int DST_Y_TOP_TO_BOTTOM ; 
 int /*<<< orphan*/  DST_Y_X ; 
 int FRGD_SRC_FRGD_CLR ; 
 int /*<<< orphan*/  GUI_TRAJ_CNTL ; 
 int HOST_32BPP ; 
 int HOST_8BPP ; 
 int /*<<< orphan*/  HOST_CNTL ; 
 int MIX_DST ; 
 int MIX_SRC ; 
 int /*<<< orphan*/  PAT_CNTL ; 
 int /*<<< orphan*/  PAT_REG0 ; 
 int /*<<< orphan*/  PAT_REG1 ; 
 int /*<<< orphan*/  SC_BOTTOM ; 
 int /*<<< orphan*/  SC_LEFT ; 
 int /*<<< orphan*/  SC_RIGHT ; 
 int /*<<< orphan*/  SC_TOP ; 
 int SRC_32BPP ; 
 int SRC_8BPP ; 
 int /*<<< orphan*/  SRC_CNTL ; 
 int /*<<< orphan*/  SRC_HEIGHT1_WIDTH1 ; 
 int /*<<< orphan*/  SRC_HEIGHT2_WIDTH2 ; 
 int SRC_LINE_X_LEFT_TO_RIGHT ; 
 int /*<<< orphan*/  SRC_OFF_PITCH ; 
 int /*<<< orphan*/  SRC_Y_X ; 
 int /*<<< orphan*/  SRC_Y_X_START ; 
 int /*<<< orphan*/  machfb_reset_engine (struct machfb_softc*) ; 
 int regr (struct machfb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (struct machfb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_fifo (struct machfb_softc*,int) ; 
 int /*<<< orphan*/  wait_for_idle (struct machfb_softc*) ; 

__attribute__((used)) static void
machfb_init_engine(struct machfb_softc *sc)
{
	uint32_t pitch_value;

	pitch_value = sc->sc_width;

	if (sc->sc_depth == 24)
		pitch_value *= 3;

	machfb_reset_engine(sc);

	wait_for_fifo(sc, 14);

	regw(sc, CONTEXT_MASK, 0xffffffff);

	regw(sc, DST_OFF_PITCH, (pitch_value / 8) << 22);

	regw(sc, DST_Y_X, 0);
	regw(sc, DST_HEIGHT, 0);
	regw(sc, DST_BRES_ERR, 0);
	regw(sc, DST_BRES_INC, 0);
	regw(sc, DST_BRES_DEC, 0);

	regw(sc, DST_CNTL, DST_LAST_PEL | DST_X_LEFT_TO_RIGHT |
	    DST_Y_TOP_TO_BOTTOM);

	regw(sc, SRC_OFF_PITCH, (pitch_value / 8) << 22);

	regw(sc, SRC_Y_X, 0);
	regw(sc, SRC_HEIGHT1_WIDTH1, 1);
	regw(sc, SRC_Y_X_START, 0);
	regw(sc, SRC_HEIGHT2_WIDTH2, 1);

	regw(sc, SRC_CNTL, SRC_LINE_X_LEFT_TO_RIGHT);

	wait_for_fifo(sc, 13);
	regw(sc, HOST_CNTL, 0);

	regw(sc, PAT_REG0, 0);
	regw(sc, PAT_REG1, 0);
	regw(sc, PAT_CNTL, 0);

	regw(sc, SC_LEFT, 0);
	regw(sc, SC_TOP, 0);
	regw(sc, SC_BOTTOM, sc->sc_height - 1);
	regw(sc, SC_RIGHT, pitch_value - 1);

	regw(sc, DP_BKGD_CLR, 0);
	regw(sc, DP_FRGD_CLR, 0xffffffff);
	regw(sc, DP_WRITE_MASK, 0xffffffff);
	regw(sc, DP_MIX, (MIX_SRC << 16) | MIX_DST);

	regw(sc, DP_SRC, FRGD_SRC_FRGD_CLR);

	wait_for_fifo(sc, 3);
	regw(sc, CLR_CMP_CLR, 0);
	regw(sc, CLR_CMP_MASK, 0xffffffff);
	regw(sc, CLR_CMP_CNTL, 0);

	wait_for_fifo(sc, 2);
	switch (sc->sc_depth) {
	case 8:
		regw(sc, DP_PIX_WIDTH, HOST_8BPP | SRC_8BPP | DST_8BPP);
		regw(sc, DP_CHAIN_MASK, DP_CHAIN_8BPP);
		regw(sc, DAC_CNTL, regr(sc, DAC_CNTL) | DAC_8BIT_EN);
		break;
#if 0
	case 32:
		regw(sc, DP_PIX_WIDTH, HOST_32BPP | SRC_32BPP | DST_32BPP);
		regw(sc, DP_CHAIN_MASK, DP_CHAIN_32BPP);
		regw(sc, DAC_CNTL, regr(sc, DAC_CNTL) | DAC_8BIT_EN);
		break;
#endif
	}

	wait_for_fifo(sc, 2);
	regw(sc, CRTC_INT_CNTL, regr(sc, CRTC_INT_CNTL) & ~0x20);
	regw(sc, GUI_TRAJ_CNTL, DST_X_LEFT_TO_RIGHT | DST_Y_TOP_TO_BOTTOM);

	wait_for_idle(sc);
}