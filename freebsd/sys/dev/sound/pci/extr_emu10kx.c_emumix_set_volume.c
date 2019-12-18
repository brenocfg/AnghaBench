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
struct emu_sc_info {int* mixer_volcache; int /*<<< orphan*/ * mixer_gpr; } ;

/* Variables and functions */
 int NUM_MIXERS ; 
 int /*<<< orphan*/  RANGE (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emumix_set_fxvol (struct emu_sc_info*,int /*<<< orphan*/ ,int) ; 

void
emumix_set_volume(struct emu_sc_info *sc, int mixer_idx, int volume)
{

	RANGE(volume, 0, 100);
	if (mixer_idx < NUM_MIXERS) {
		sc->mixer_volcache[mixer_idx] = volume;
		emumix_set_fxvol(sc, sc->mixer_gpr[mixer_idx], volume);
	}
}