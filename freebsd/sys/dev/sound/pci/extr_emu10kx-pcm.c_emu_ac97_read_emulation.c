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
struct emu_pcm_info {int* ac97_state; int /*<<< orphan*/  card; } ;

/* Variables and functions */
#define  AC97_MIX_MASTER 131 
#define  AC97_MIX_PCM 130 
#define  AC97_MIX_RGAIN 129 
#define  AC97_REG_RECSEL 128 
 int /*<<< orphan*/  EMU_AC97ADDR ; 
 int /*<<< orphan*/  EMU_AC97DATA ; 
 int emu_rd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emu_wr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
emu_ac97_read_emulation(struct emu_pcm_info *sc, int regno)
{
	int use_ac97;
	int emulated;
	int tmp;

	use_ac97 = 1;
	emulated = 0;

	switch (regno) {
	case AC97_MIX_MASTER:
		emulated = sc->ac97_state[AC97_MIX_MASTER];
		use_ac97 = 0;
		break;
	case AC97_MIX_PCM:
		emulated = sc->ac97_state[AC97_MIX_PCM];
		use_ac97 = 0;
		break;
	case AC97_REG_RECSEL:
		emulated = 0x0505;
		use_ac97 = 0;
		break;
	case AC97_MIX_RGAIN:
		emulated = sc->ac97_state[AC97_MIX_RGAIN];
		use_ac97 = 0;
		break;
	}

	emu_wr(sc->card, EMU_AC97ADDR, regno, 1);
	tmp = emu_rd(sc->card, EMU_AC97DATA, 2);

	if (use_ac97)
		emulated = tmp;

	return (emulated);
}