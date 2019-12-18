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
struct creator_softc {int sc_bg_cache; int sc_fg_cache; int sc_fontinc_cache; int sc_fontw_cache; int sc_pmask_cache; scalar_t__ sc_fifo_cache; } ;

/* Variables and functions */
 int FBC_PPC_APE_DIS ; 
 int FBC_PPC_CS_CONST ; 
 int FBC_PPC_TBE_OPAQUE ; 
 int FBC_PPC_VCE_DIS ; 
 int /*<<< orphan*/  FFB_FBC ; 
 int /*<<< orphan*/  FFB_FBC_FBC ; 
 int /*<<< orphan*/  FFB_FBC_PPC ; 
 int FFB_FBC_RB_A ; 
 int FFB_FBC_RGBE_MASK ; 
 int FFB_FBC_SB_BOTH ; 
 int FFB_FBC_WB_A ; 
 int FFB_FBC_XE_OFF ; 
 int /*<<< orphan*/  FFB_WRITE (struct creator_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  creator_ras_fifo_wait (struct creator_softc*,int) ; 
 int /*<<< orphan*/  creator_ras_wait (struct creator_softc*) ; 

__attribute__((used)) static int
creator_set_mode(video_adapter_t *adp, int mode)
{
	struct creator_softc *sc;

	sc = (struct creator_softc *)adp;
	sc->sc_bg_cache = -1;
	sc->sc_fg_cache = -1;
	sc->sc_fontinc_cache = -1;
	sc->sc_fontw_cache = -1;
	sc->sc_pmask_cache = -1;

	creator_ras_wait(sc);
	sc->sc_fifo_cache = 0;
	creator_ras_fifo_wait(sc, 2);
	FFB_WRITE(sc, FFB_FBC, FFB_FBC_PPC, FBC_PPC_VCE_DIS |
	    FBC_PPC_TBE_OPAQUE | FBC_PPC_APE_DIS | FBC_PPC_CS_CONST);
	FFB_WRITE(sc, FFB_FBC, FFB_FBC_FBC, FFB_FBC_WB_A | FFB_FBC_RB_A |
	    FFB_FBC_SB_BOTH | FFB_FBC_XE_OFF | FFB_FBC_RGBE_MASK);
	return (0);
}