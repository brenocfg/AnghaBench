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
struct emu_sc_info {int rev; int mode; int /*<<< orphan*/ * mute_gpr; scalar_t__ is_ca0108; scalar_t__ is_ca0102; scalar_t__ is_emu10k2; int /*<<< orphan*/  dev; scalar_t__ broken_digital; scalar_t__ is_emu10k1; } ;

/* Variables and functions */
 size_t ANALOGMUTE ; 
 int /*<<< orphan*/  EMU_A_IOCFG ; 
 int EMU_A_IOCFG_DISABLE_ANALOG ; 
 int EMU_A_IOCFG_GPOUT1 ; 
 int /*<<< orphan*/  EMU_HCFG ; 
 int EMU_HCFG_AUDIOENABLE ; 
 int EMU_HCFG_AUTOMUTE ; 
 int EMU_HCFG_CODECFMT_I2S ; 
 int EMU_HCFG_GPOUT0 ; 
 int EMU_HCFG_JOYENABLE ; 
 int EMU_HCFG_LOCKTANKCACHE_MASK ; 
#define  MODE_ANALOG 129 
#define  MODE_DIGITAL 128 
 int /*<<< orphan*/  SPDIF_MODE_PCM ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int emu_rd (struct emu_sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wr (struct emu_sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emumix_set_gpr (struct emu_sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emumix_set_spdif_mode (struct emu_sc_info*,int /*<<< orphan*/ ) ; 

void
emumix_set_mode(struct emu_sc_info *sc, int mode)
{
	uint32_t a_iocfg;
	uint32_t hcfg;
	uint32_t tmp;

	switch (mode) {
	case MODE_DIGITAL:
		/* FALLTHROUGH */
	case MODE_ANALOG:
		break;
	default:
		return;
	}

	hcfg = EMU_HCFG_AUDIOENABLE | EMU_HCFG_AUTOMUTE;
	a_iocfg = 0;

	if (sc->rev >= 6)
		hcfg |= EMU_HCFG_JOYENABLE;

	if (sc->is_emu10k1)
		hcfg |= EMU_HCFG_LOCKTANKCACHE_MASK;
	else
		hcfg |= EMU_HCFG_CODECFMT_I2S | EMU_HCFG_JOYENABLE;


	if (mode == MODE_DIGITAL) {
		if (sc->broken_digital) {
			device_printf(sc->dev, "Digital mode is reported as broken on this card.\n");
		}
		a_iocfg |= EMU_A_IOCFG_GPOUT1;
		hcfg |= EMU_HCFG_GPOUT0;
	}

	if (mode == MODE_ANALOG)
		emumix_set_spdif_mode(sc, SPDIF_MODE_PCM);

	if (sc->is_emu10k2)
		a_iocfg |= 0x80; /* XXX */

	if ((sc->is_ca0102) || (sc->is_ca0108))
		/*
		 * Setting EMU_A_IOCFG_DISABLE_ANALOG will do opposite things
		 * on diffrerent cards.
		 * "don't disable analog outs" on Audigy 2 (ca0102/ca0108)
		 * "disable analog outs" on Audigy (emu10k2)
		 */
		a_iocfg |= EMU_A_IOCFG_DISABLE_ANALOG;

	if (sc->is_ca0108)
		a_iocfg |= 0x20; /* XXX */

	/* Mute analog center & subwoofer before mode change */
	if (mode == MODE_DIGITAL)
		emumix_set_gpr(sc, sc->mute_gpr[ANALOGMUTE], 1);

	emu_wr(sc, EMU_HCFG, hcfg, 4);

	if ((sc->is_emu10k2) || (sc->is_ca0102) || (sc->is_ca0108)) {
		tmp = emu_rd(sc, EMU_A_IOCFG, 2);
		tmp = a_iocfg;
		emu_wr(sc, EMU_A_IOCFG, tmp, 2);
	}

	/* Unmute if we have changed mode to analog. */

	if (mode == MODE_ANALOG)
		emumix_set_gpr(sc, sc->mute_gpr[ANALOGMUTE], 0);

	sc->mode = mode;
}