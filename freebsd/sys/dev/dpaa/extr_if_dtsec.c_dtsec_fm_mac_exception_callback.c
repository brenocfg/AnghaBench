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
typedef  struct dtsec_softc* t_Handle ;
struct dtsec_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  e_FmMacExceptions ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtsec_fm_mac_ex_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtsec_fm_mac_exception_callback(t_Handle app, e_FmMacExceptions exception)
{
	struct dtsec_softc *sc;

	sc = app;
	device_printf(sc->sc_dev, "MAC exception %i: %s.\n", exception,
	    dtsec_fm_mac_ex_to_str(exception));
}