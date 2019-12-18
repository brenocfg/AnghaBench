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
struct umidi_chan {int /*<<< orphan*/  mtx; } ;
struct uaudio_softc {struct umidi_chan sc_midi_chan; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 struct uaudio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
umidi_init(device_t dev)
{
	struct uaudio_softc *sc = device_get_softc(dev);
	struct umidi_chan *chan = &sc->sc_midi_chan;

	mtx_init(&chan->mtx, "umidi lock", NULL, MTX_DEF | MTX_RECURSE);
}