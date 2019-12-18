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
struct emu_sc_info {int* mixer_volcache; } ;

/* Variables and functions */
 int NUM_MIXERS ; 

int
emumix_get_volume(struct emu_sc_info *sc, int mixer_idx)
{
	if ((mixer_idx < NUM_MIXERS) && (mixer_idx >= 0))
		return (sc->mixer_volcache[mixer_idx]);
	return (-1);
}