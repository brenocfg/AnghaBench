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
struct twl_softc {int sc_type; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 
#define  TWL_DEVICE_4030 131 
#define  TWL_DEVICE_6025 130 
#define  TWL_DEVICE_6030 129 
#define  TWL_DEVICE_UNKNOWN 128 
 struct twl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static int
twl_probe(device_t dev)
{
	phandle_t node;
	const char *compat;
	int len, l;
	struct twl_softc *sc;

	if ((compat = ofw_bus_get_compat(dev)) == NULL)
		return (ENXIO);

	if ((node = ofw_bus_get_node(dev)) == 0)
		return (ENXIO);

	/* Get total 'compatible' prop len */
	if ((len = OF_getproplen(node, "compatible")) <= 0)
		return (ENXIO);

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_type = TWL_DEVICE_UNKNOWN;

	while (len > 0) {
		if (strncasecmp(compat, "ti,twl6030", 10) == 0)
			sc->sc_type = TWL_DEVICE_6030;
		else if (strncasecmp(compat, "ti,twl6025", 10) == 0)
			sc->sc_type = TWL_DEVICE_6025;
		else if (strncasecmp(compat, "ti,twl4030", 10) == 0)
			sc->sc_type = TWL_DEVICE_4030;
		
		if (sc->sc_type != TWL_DEVICE_UNKNOWN)
			break;

		/* Slide to the next sub-string. */
		l = strlen(compat) + 1;
		compat += l;
		len -= l;
	}
	
	switch (sc->sc_type) {
	case TWL_DEVICE_4030:
		device_set_desc(dev, "TI TWL4030/TPS659x0 Companion IC");
		break;
	case TWL_DEVICE_6025:
		device_set_desc(dev, "TI TWL6025 Companion IC");
		break;
	case TWL_DEVICE_6030:
		device_set_desc(dev, "TI TWL6030 Companion IC");
		break;
	case TWL_DEVICE_UNKNOWN:
	default:
		return (ENXIO);
	}
	
	return (0);
}