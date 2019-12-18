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
struct scc_softc {int /*<<< orphan*/ * sc_class; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SBUS_RCLK ; 
 int /*<<< orphan*/  SBUS_REGSHFT ; 
 struct scc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int scc_bfe_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_z8530_class ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int
scc_sbus_probe(device_t dev)
{
	struct scc_softc *sc;
	const char *nm;

	sc = device_get_softc(dev);
	nm = ofw_bus_get_name(dev);
	if (!strcmp(nm, "zs")) {
		device_set_desc(dev, "Zilog Z8530 dual channel SCC");
		sc->sc_class = &scc_z8530_class;
		return (scc_bfe_probe(dev, SBUS_REGSHFT, SBUS_RCLK, 0));
	}
	return (ENXIO);
}