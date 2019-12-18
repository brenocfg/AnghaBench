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
typedef  int uint32_t ;
struct emu_voice {int sa; int start; int ea; int end; int* routing; int* amounts; struct emu_voice* slave; scalar_t__ stereo; int /*<<< orphan*/  vnum; scalar_t__ b16; } ;
struct TYPE_2__ {scalar_t__ silent_page_addr; } ;
struct emu_sc_info {TYPE_1__ mem; scalar_t__ is_emu10k1; } ;

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
 int /*<<< orphan*/  emu_wrptr (struct emu_sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
emu_vwrite(struct emu_sc_info *sc, struct emu_voice *v)
{
	int s;
	uint32_t start, val, silent_page;

	s = (v->stereo ? 1 : 0) + (v->b16 ? 1 : 0);

	v->sa = v->start >> s;
	v->ea = v->end >> s;


	if (v->stereo) {
		emu_wrptr(sc, v->vnum, EMU_CHAN_CPF, EMU_CHAN_CPF_STEREO_MASK);
	} else {
		emu_wrptr(sc, v->vnum, EMU_CHAN_CPF, 0);
	}
	val = v->stereo ? 28 : 30;
	val *= v->b16 ? 1 : 2;
	start = v->sa + val;

	if (sc->is_emu10k1) {
		emu_wrptr(sc, v->vnum, EMU_CHAN_FXRT, ((v->routing[3] << 12) |
		    (v->routing[2] << 8) |
		    (v->routing[1] << 4) |
		    (v->routing[0] << 0)) << 16);
	} else {
		emu_wrptr(sc, v->vnum, EMU_A_CHAN_FXRT1, (v->routing[3] << 24) |
		    (v->routing[2] << 16) |
		    (v->routing[1] << 8) |
		    (v->routing[0] << 0));
		emu_wrptr(sc, v->vnum, EMU_A_CHAN_FXRT2, (v->routing[7] << 24) |
		    (v->routing[6] << 16) |
		    (v->routing[5] << 8) |
		    (v->routing[4] << 0));
		emu_wrptr(sc, v->vnum, EMU_A_CHAN_SENDAMOUNTS, (v->amounts[7] << 24) |
		    (v->amounts[6] << 26) |
		    (v->amounts[5] << 8) |
		    (v->amounts[4] << 0));
	}
	emu_wrptr(sc, v->vnum, EMU_CHAN_PTRX, (v->amounts[0] << 8) | (v->amounts[1] << 0));
	emu_wrptr(sc, v->vnum, EMU_CHAN_DSL, v->ea | (v->amounts[3] << 24));
	emu_wrptr(sc, v->vnum, EMU_CHAN_PSST, v->sa | (v->amounts[2] << 24));

	emu_wrptr(sc, v->vnum, EMU_CHAN_CCCA, start | (v->b16 ? 0 : EMU_CHAN_CCCA_8BITSELECT));
	emu_wrptr(sc, v->vnum, EMU_CHAN_Z1, 0);
	emu_wrptr(sc, v->vnum, EMU_CHAN_Z2, 0);

	silent_page = ((uint32_t) (sc->mem.silent_page_addr) << 1) | EMU_CHAN_MAP_PTI_MASK;
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

	emu_wrptr(sc, v->vnum, EMU_CHAN_ATKHLDV, EMU_CHAN_ATKHLDV_HOLDTIME_MASK | EMU_CHAN_ATKHLDV_ATTACKTIME_MASK);
	emu_wrptr(sc, v->vnum, EMU_CHAN_ENVVOL, 0x8000);

	emu_wrptr(sc, v->vnum, EMU_CHAN_PEFE_FILTERAMOUNT, 0x7f);
	emu_wrptr(sc, v->vnum, EMU_CHAN_PEFE_PITCHAMOUNT, 0);
	if ((v->stereo) && (v->slave != NULL))
		emu_vwrite(sc, v->slave);
}