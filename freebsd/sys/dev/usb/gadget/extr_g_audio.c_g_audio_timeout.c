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
struct g_audio_softc {scalar_t__ sc_mode; int /*<<< orphan*/ * sc_xfer; scalar_t__* sc_pattern; int /*<<< orphan*/  sc_pattern_len; } ;

/* Variables and functions */
 size_t G_AUDIO_ISOC0_WR ; 
 size_t G_AUDIO_ISOC1_WR ; 
 int G_AUDIO_MAX_STRLEN ; 
 scalar_t__ G_AUDIO_MODE_LOOP ; 
 scalar_t__ g_audio_mode ; 
 int /*<<< orphan*/  g_audio_pattern_data ; 
 int /*<<< orphan*/  g_audio_timeout_reset (struct g_audio_softc*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_audio_timeout(void *arg)
{
	struct g_audio_softc *sc = arg;

	sc->sc_mode = g_audio_mode;

	memcpy(sc->sc_pattern, g_audio_pattern_data, sizeof(sc->sc_pattern));

	sc->sc_pattern[G_AUDIO_MAX_STRLEN - 1] = 0;

	sc->sc_pattern_len = strlen(sc->sc_pattern);

	if (sc->sc_mode != G_AUDIO_MODE_LOOP) {
		usbd_transfer_start(sc->sc_xfer[G_AUDIO_ISOC0_WR]);
		usbd_transfer_start(sc->sc_xfer[G_AUDIO_ISOC1_WR]);
	}
	g_audio_timeout_reset(sc);
}