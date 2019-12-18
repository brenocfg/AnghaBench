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
struct g_audio_softc {int sc_noise_rem; } ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static int32_t
g_noise(struct g_audio_softc *sc)
{
	uint32_t temp;
	const uint32_t prime = 0xFFFF1D;

	if (sc->sc_noise_rem & 1) {
		sc->sc_noise_rem += prime;
	}
	sc->sc_noise_rem /= 2;

	temp = sc->sc_noise_rem;

	/* unsigned to signed conversion */

	temp ^= 0x800000;
	if (temp & 0x800000) {
		temp |= (-0x800000);
	}
	return temp;
}