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
struct ath_softc {int /*<<< orphan*/ * sc_spectral; int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  ath_hal_spectral_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ath_spectral_detach(struct ath_softc *sc)
{

	if (! ath_hal_spectral_supported(sc->sc_ah))
		return (0);

	if (sc->sc_spectral != NULL) {
		free(sc->sc_spectral, M_TEMP);
	}
	return (0);
}