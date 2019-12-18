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
 int /*<<< orphan*/  EBUS_RCLK ; 
 int /*<<< orphan*/  EBUS_REGSHFT ; 
 int ENXIO ; 
 struct scc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int scc_bfe_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_sab82532_class ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int
scc_ebus_probe(device_t dev)
{
	struct scc_softc *sc;
	const char *cmpt, *nm;

	sc = device_get_softc(dev);
	nm = ofw_bus_get_name(dev);
	cmpt = ofw_bus_get_compat(dev);
	if (cmpt == NULL)
		cmpt = "";
	if (!strcmp(nm, "se") || !strcmp(nm, "FJSV,se") ||
	    !strcmp(cmpt, "sab82532")) {
		device_set_desc(dev, "Siemens SAB 82532 dual channel SCC");
		sc->sc_class = &scc_sab82532_class;
		return (scc_bfe_probe(dev, EBUS_REGSHFT, EBUS_RCLK, 0));
	}
	return (ENXIO);
}