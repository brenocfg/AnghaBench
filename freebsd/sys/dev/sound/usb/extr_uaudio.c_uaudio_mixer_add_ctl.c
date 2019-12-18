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
typedef  scalar_t__ uint8_t ;
struct uaudio_softc {int /*<<< orphan*/  sc_audio_rev; int /*<<< orphan*/  sc_udev; } ;
struct uaudio_mixer_node {size_t class; scalar_t__ type; int minval; int maxval; int mul; scalar_t__ nchan; int /*<<< orphan*/  ctl; int /*<<< orphan*/  wIndex; int /*<<< orphan*/ * wValue; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int /*<<< orphan*/  GET_MAX ; 
 int /*<<< orphan*/  GET_MIN ; 
 int /*<<< orphan*/  GET_RES ; 
 scalar_t__ MIX_ON_OFF ; 
 scalar_t__ MIX_SELECTOR ; 
 size_t UAC_NCLASSES ; 
 int /*<<< orphan*/ * uac_names ; 
 int uaudio_debug ; 
 int /*<<< orphan*/  uaudio_mixer_add_ctl_sub (struct uaudio_softc*,struct uaudio_mixer_node*) ; 
 void* uaudio_mixer_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uaudio_mixer_node*) ; 

__attribute__((used)) static void
uaudio_mixer_add_ctl(struct uaudio_softc *sc, struct uaudio_mixer_node *mc)
{
	int32_t res;

	if (mc->class < UAC_NCLASSES) {
		DPRINTF("adding %s.%d\n",
		    uac_names[mc->class], mc->ctl);
	} else {
		DPRINTF("adding %d\n", mc->ctl);
	}

	if (mc->type == MIX_ON_OFF) {
		mc->minval = 0;
		mc->maxval = 1;
	} else if (mc->type == MIX_SELECTOR) {
	} else {

		/* determine min and max values */

		mc->minval = uaudio_mixer_get(sc->sc_udev,
		    sc->sc_audio_rev, GET_MIN, mc);
		mc->maxval = uaudio_mixer_get(sc->sc_udev,
		    sc->sc_audio_rev, GET_MAX, mc);

		/* check if max and min was swapped */

		if (mc->maxval < mc->minval) {
			res = mc->maxval;
			mc->maxval = mc->minval;
			mc->minval = res;
		}

		/* compute value range */
		mc->mul = mc->maxval - mc->minval;
		if (mc->mul == 0)
			mc->mul = 1;

		/* compute value alignment */
		res = uaudio_mixer_get(sc->sc_udev,
		    sc->sc_audio_rev, GET_RES, mc);

		DPRINTF("Resolution = %d\n", (int)res);
	}

	uaudio_mixer_add_ctl_sub(sc, mc);

#ifdef USB_DEBUG
	if (uaudio_debug > 2) {
		uint8_t i;

		for (i = 0; i < mc->nchan; i++) {
			DPRINTF("[mix] wValue=%04x\n", mc->wValue[0]);
		}
		DPRINTF("[mix] wIndex=%04x type=%d ctl='%d' "
		    "min=%d max=%d\n",
		    mc->wIndex, mc->type, mc->ctl,
		    mc->minval, mc->maxval);
	}
#endif
}