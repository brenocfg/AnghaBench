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
struct uaudio_softc {struct uaudio_mixer_node* sc_mixer_root; } ;
struct uaudio_mixer_node {unsigned int ctl; int nchan; struct uaudio_mixer_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  uaudio_mixer_ctl_set (struct uaudio_softc*,struct uaudio_mixer_node*,int,int) ; 

void
uaudio_mixer_set(struct uaudio_softc *sc, unsigned type,
    unsigned left, unsigned right)
{
	struct uaudio_mixer_node *mc;
	int chan;

	for (mc = sc->sc_mixer_root; mc != NULL; mc = mc->next) {

		if (mc->ctl == type) {
			for (chan = 0; chan < mc->nchan; chan++) {
				uaudio_mixer_ctl_set(sc, mc, chan,
				    (int)((chan == 0 ? left : right) *
				    255) / 100);
			}
		}
	}
}