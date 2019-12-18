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
struct g_audio_softc {scalar_t__ sc_state; scalar_t__ sc_pattern_len; int* sc_pattern; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int g_noise (struct g_audio_softc*) ; 

__attribute__((used)) static void
g_audio_make_samples(struct g_audio_softc *sc, int16_t *ptr, int samples)
{
	int i;
	int j;

	for (i = 0; i != samples; i++) {

		j = g_noise(sc);

		if ((sc->sc_state < 0) || (sc->sc_state >= sc->sc_pattern_len))
			sc->sc_state = 0;

		if (sc->sc_pattern_len != 0) {
			j = (j * sc->sc_pattern[sc->sc_state]) >> 16;
			sc->sc_state++;
		}
		*ptr++ = j / 256;
		*ptr++ = j / 256;
	}
}