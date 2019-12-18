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
struct uaudio_softc {struct uaudio_mixer_node* sc_mixer_root; } ;
struct uaudio_mixer_node {scalar_t__ ctl; scalar_t__ type; int minval; int maxval; int* slctrtype; struct uaudio_mixer_node* next; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ MIX_SELECTOR ; 
 scalar_t__ SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  uaudio_mixer_ctl_set (struct uaudio_softc*,struct uaudio_mixer_node*,int /*<<< orphan*/ ,int) ; 

uint32_t
uaudio_mixer_setrecsrc(struct uaudio_softc *sc, uint32_t src)
{
	struct uaudio_mixer_node *mc;
	uint32_t mask;
	uint32_t temp;
	int32_t i;

	for (mc = sc->sc_mixer_root; mc;
	    mc = mc->next) {

		if ((mc->ctl == SOUND_MIXER_NRDEVICES) &&
		    (mc->type == MIX_SELECTOR)) {

			/* compute selector mask */

			mask = 0;
			for (i = mc->minval; (i > 0) && (i <= mc->maxval); i++) {
				mask |= (1 << mc->slctrtype[i - 1]);
			}

			temp = mask & src;
			if (temp == 0) {
				continue;
			}
			/* find the first set bit */
			temp = (-temp) & temp;

			/* update "src" */
			src &= ~mask;
			src |= temp;

			for (i = mc->minval; (i > 0) && (i <= mc->maxval); i++) {
				if (temp != (1 << mc->slctrtype[i - 1])) {
					continue;
				}
				uaudio_mixer_ctl_set(sc, mc, 0, i);
				break;
			}
		}
	}
	return (src);
}