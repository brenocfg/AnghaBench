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
struct uhso_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_tty; int /*<<< orphan*/  sc_super_ucom; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  device_free_softc (struct uhso_softc*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ ucom_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uhso_free_softc(struct uhso_softc *sc)
{
	if (ucom_unref(&sc->sc_super_ucom)) {
		free(sc->sc_tty, M_USBDEV);
		free(sc->sc_ucom, M_USBDEV);
		mtx_destroy(&sc->sc_mtx);
		device_free_softc(sc);
	}
}