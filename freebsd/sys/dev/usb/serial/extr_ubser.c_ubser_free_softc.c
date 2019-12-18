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
struct ubser_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_super_ucom; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_free_softc (struct ubser_softc*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ ucom_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ubser_free_softc(struct ubser_softc *sc)
{
	if (ucom_unref(&sc->sc_super_ucom)) {
		mtx_destroy(&sc->sc_mtx);
		device_free_softc(sc);
	}
}