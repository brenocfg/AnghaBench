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
struct uaudio_softc {int sc_mix_info; int sc_recsrc_info; struct uaudio_mixer_node* sc_mixer_root; } ;
struct uaudio_mixer_node {int ctl; scalar_t__ type; int minval; int maxval; int* slctrtype; struct uaudio_mixer_node* next; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ MIX_SELECTOR ; 
 int SOUND_MIXER_NRDEVICES ; 

__attribute__((used)) static void
uaudio_mixer_init(struct uaudio_softc *sc)
{
	struct uaudio_mixer_node *mc;
	int32_t i;

	for (mc = sc->sc_mixer_root; mc;
	    mc = mc->next) {

		if (mc->ctl != SOUND_MIXER_NRDEVICES) {
			/*
			 * Set device mask bits. See
			 * /usr/include/machine/soundcard.h
			 */
			sc->sc_mix_info |= (1 << mc->ctl);
		}
		if ((mc->ctl == SOUND_MIXER_NRDEVICES) &&
		    (mc->type == MIX_SELECTOR)) {

			for (i = mc->minval; (i > 0) && (i <= mc->maxval); i++) {
				if (mc->slctrtype[i - 1] == SOUND_MIXER_NRDEVICES) {
					continue;
				}
				sc->sc_recsrc_info |= 1 << mc->slctrtype[i - 1];
			}
		}
	}
}