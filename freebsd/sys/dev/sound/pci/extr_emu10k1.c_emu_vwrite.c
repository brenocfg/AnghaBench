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
typedef  int u_int32_t ;
struct TYPE_2__ {scalar_t__ silent_page_addr; } ;
struct sc_info {TYPE_1__ mem; scalar_t__ audigy; } ;
struct emu_voice {int start; int end; int vol; int fxrt1; int fxrt2; struct emu_voice* slave; int /*<<< orphan*/  vnum; scalar_t__ b16; scalar_t__ stereo; scalar_t__ ismaster; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_A_CHAN_FXRT1 ; 
 int /*<<< orphan*/  EMU_A_CHAN_FXRT2 ; 
 int /*<<< orphan*/  EMU_A_CHAN_SENDAMOUNTS ; 
 int /*<<< orphan*/  EMU_CHAN_ATKHLDM ; 
 int /*<<< orphan*/  EMU_CHAN_ATKHLDV ; 
 int EMU_CHAN_ATKHLDV_ATTACKTIME_MASK ; 
 int EMU_CHAN_ATKHLDV_HOLDTIME_MASK ; 
 int /*<<< orphan*/  EMU_CHAN_CCCA ; 
 int EMU_CHAN_CCCA_8BITSELECT ; 
 int /*<<< orphan*/  EMU_CHAN_CPF ; 
 int EMU_CHAN_CPF_STEREO_MASK ; 
 int /*<<< orphan*/  EMU_CHAN_CVCF ; 
 int EMU_CHAN_CVCF_CURRFILTER_MASK ; 
 int /*<<< orphan*/  EMU_CHAN_DCYSUSM ; 
 int EMU_CHAN_DCYSUSM_DECAYTIME_MASK ; 
 int /*<<< orphan*/  EMU_CHAN_DSL ; 
 int /*<<< orphan*/  EMU_CHAN_ENVVAL ; 
 int /*<<< orphan*/  EMU_CHAN_ENVVOL ; 
 int /*<<< orphan*/  EMU_CHAN_FM2FRQ2 ; 
 int /*<<< orphan*/  EMU_CHAN_FMMOD ; 
 int /*<<< orphan*/  EMU_CHAN_FXRT ; 
 int /*<<< orphan*/  EMU_CHAN_LFOVAL1 ; 
 int /*<<< orphan*/  EMU_CHAN_LFOVAL2 ; 
 int /*<<< orphan*/  EMU_CHAN_MAPA ; 
 int /*<<< orphan*/  EMU_CHAN_MAPB ; 
 int EMU_CHAN_MAP_PTI_MASK ; 
 int /*<<< orphan*/  EMU_CHAN_PEFE_FILTERAMOUNT ; 
 int /*<<< orphan*/  EMU_CHAN_PEFE_PITCHAMOUNT ; 
 int /*<<< orphan*/  EMU_CHAN_PSST ; 
 int /*<<< orphan*/  EMU_CHAN_PTRX ; 
 int /*<<< orphan*/  EMU_CHAN_TREMFRQ ; 
 int /*<<< orphan*/  EMU_CHAN_VTFT ; 
 int EMU_CHAN_VTFT_FILTERTARGET_MASK ; 
 int /*<<< orphan*/  EMU_CHAN_Z1 ; 
 int /*<<< orphan*/  EMU_CHAN_Z2 ; 
 int /*<<< orphan*/  emu_wrptr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
emu_vwrite(struct sc_info *sc, struct emu_voice *v)
{
	int s;
	int l, r, x, y;
	u_int32_t sa, ea, start, val, silent_page;

	s = (v->stereo ? 1 : 0) + (v->b16 ? 1 : 0);

	sa = v->start >> s;
	ea = v->end >> s;

	l = r = x = y = v->vol;
	if (v->stereo) {
		l = v->ismaster ? l : 0;
		r = v->ismaster ? 0 : r;
	}

	emu_wrptr(sc, v->vnum, EMU_CHAN_CPF, v->stereo ? EMU_CHAN_CPF_STEREO_MASK : 0);
	val = v->stereo ? 28 : 30;
	val *= v->b16 ? 1 : 2;
	start = sa + val;

	if (sc->audigy) {
		emu_wrptr(sc, v->vnum, EMU_A_CHAN_FXRT1, v->fxrt1);
		emu_wrptr(sc, v->vnum, EMU_A_CHAN_FXRT2, v->fxrt2);
		emu_wrptr(sc, v->vnum, EMU_A_CHAN_SENDAMOUNTS, 0);
	}
	else
		emu_wrptr(sc, v->vnum, EMU_CHAN_FXRT, v->fxrt1 << 16);

	emu_wrptr(sc, v->vnum, EMU_CHAN_PTRX, (x << 8) | r);
	emu_wrptr(sc, v->vnum, EMU_CHAN_DSL, ea | (y << 24));
	emu_wrptr(sc, v->vnum, EMU_CHAN_PSST, sa | (l << 24));
	emu_wrptr(sc, v->vnum, EMU_CHAN_CCCA, start | (v->b16 ? 0 : EMU_CHAN_CCCA_8BITSELECT));

	emu_wrptr(sc, v->vnum, EMU_CHAN_Z1, 0);
	emu_wrptr(sc, v->vnum, EMU_CHAN_Z2, 0);

	silent_page = ((u_int32_t)(sc->mem.silent_page_addr) << 1)
	    | EMU_CHAN_MAP_PTI_MASK;
	emu_wrptr(sc, v->vnum, EMU_CHAN_MAPA, silent_page);
	emu_wrptr(sc, v->vnum, EMU_CHAN_MAPB, silent_page);

	emu_wrptr(sc, v->vnum, EMU_CHAN_CVCF, EMU_CHAN_CVCF_CURRFILTER_MASK);
	emu_wrptr(sc, v->vnum, EMU_CHAN_VTFT, EMU_CHAN_VTFT_FILTERTARGET_MASK);
	emu_wrptr(sc, v->vnum, EMU_CHAN_ATKHLDM, 0);
	emu_wrptr(sc, v->vnum, EMU_CHAN_DCYSUSM, EMU_CHAN_DCYSUSM_DECAYTIME_MASK);
	emu_wrptr(sc, v->vnum, EMU_CHAN_LFOVAL1, 0x8000);
	emu_wrptr(sc, v->vnum, EMU_CHAN_LFOVAL2, 0x8000);
	emu_wrptr(sc, v->vnum, EMU_CHAN_FMMOD, 0);
	emu_wrptr(sc, v->vnum, EMU_CHAN_TREMFRQ, 0);
	emu_wrptr(sc, v->vnum, EMU_CHAN_FM2FRQ2, 0);
	emu_wrptr(sc, v->vnum, EMU_CHAN_ENVVAL, 0x8000);

	emu_wrptr(sc, v->vnum, EMU_CHAN_ATKHLDV,
	    EMU_CHAN_ATKHLDV_HOLDTIME_MASK | EMU_CHAN_ATKHLDV_ATTACKTIME_MASK);
	emu_wrptr(sc, v->vnum, EMU_CHAN_ENVVOL, 0x8000);

	emu_wrptr(sc, v->vnum, EMU_CHAN_PEFE_FILTERAMOUNT, 0x7f);
	emu_wrptr(sc, v->vnum, EMU_CHAN_PEFE_PITCHAMOUNT, 0);

	if (v->slave != NULL)
		emu_vwrite(sc, v->slave);
}