#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ num_alt; scalar_t__ running; } ;
struct TYPE_4__ {scalar_t__ num_alt; scalar_t__ running; int /*<<< orphan*/  set_alt; } ;
struct uaudio_softc {TYPE_1__ sc_rec_chan; TYPE_2__ sc_play_chan; } ;

/* Variables and functions */
 scalar_t__ uaudio_chan_is_async (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uaudio_chan_need_both(struct uaudio_softc *sc)
{
	return (sc->sc_play_chan.num_alt > 0 &&
	    sc->sc_play_chan.running != 0 &&
	    uaudio_chan_is_async(&sc->sc_play_chan,
	    sc->sc_play_chan.set_alt) != 0 &&
	    sc->sc_rec_chan.num_alt > 0 &&
	    sc->sc_rec_chan.running == 0);
}