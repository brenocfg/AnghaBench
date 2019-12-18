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
struct cqspi_softc {int /*<<< orphan*/  config_intrhook; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cqspi_add_devices (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cqspi_delayed_attach(void *arg)
{
	struct cqspi_softc *sc;

	sc = arg;

	cqspi_add_devices(sc->dev);
	bus_generic_attach(sc->dev);

	config_intrhook_disestablish(&sc->config_intrhook);
}