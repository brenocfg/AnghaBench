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
struct emu_sc_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU_SPCS0 ; 
 int /*<<< orphan*/  EMU_SPCS1 ; 
 int /*<<< orphan*/  EMU_SPCS2 ; 
 int EMU_SPCS_CHANNELNUM_LEFT ; 
 int EMU_SPCS_CLKACCY_1000PPM ; 
 int EMU_SPCS_COPYRIGHT ; 
 int EMU_SPCS_EMPHASIS_NONE ; 
 int EMU_SPCS_GENERATIONSTATUS ; 
 int EMU_SPCS_SAMPLERATE_48 ; 
 int EMU_SPCS_SOURCENUM_UNSPEC ; 
#define  SPDIF_MODE_AC3 129 
#define  SPDIF_MODE_PCM 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  emu_wrptr (struct emu_sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
emumix_set_spdif_mode(struct emu_sc_info *sc, int mode)
{
	uint32_t spcs;

	switch (mode) {
	case SPDIF_MODE_PCM:
		break;
	case SPDIF_MODE_AC3:
		device_printf(sc->dev, "AC3 mode does not work and disabled\n");
		return;
	default:
		return;
	}

	spcs = EMU_SPCS_CLKACCY_1000PPM | EMU_SPCS_SAMPLERATE_48 |
	    EMU_SPCS_CHANNELNUM_LEFT | EMU_SPCS_SOURCENUM_UNSPEC |
	    EMU_SPCS_GENERATIONSTATUS | 0x00001200 | 0x00000000 |
	    EMU_SPCS_EMPHASIS_NONE | EMU_SPCS_COPYRIGHT;

	mode = SPDIF_MODE_PCM;

	emu_wrptr(sc, 0, EMU_SPCS0, spcs);
	emu_wrptr(sc, 0, EMU_SPCS1, spcs);
	emu_wrptr(sc, 0, EMU_SPCS2, spcs);
}