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
struct pinmux_softc {int /*<<< orphan*/  dev; } ;
struct pincfg {char* function; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int pinmux_config_node (struct pinmux_softc*,char*,struct pincfg*) ; 
 int pinmux_read_node (struct pinmux_softc*,int /*<<< orphan*/ ,struct pincfg*,char**,int*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
pinmux_process_node(struct pinmux_softc *sc, phandle_t node)
{
	struct pincfg cfg;
	char *pins, *pname;
	int i, len, lpins, rv;

	rv = pinmux_read_node(sc, node, &cfg, &pins, &lpins);
	if (rv != 0)
		return (rv);

	len = 0;
	pname = pins;
	do {
		i = strlen(pname) + 1;
		rv = pinmux_config_node(sc, pname, &cfg);
		if (rv != 0)
			device_printf(sc->dev,
			    "Cannot configure pin: %s: %d\n", pname, rv);

		len += i;
		pname += i;
	} while (len < lpins);

	if (pins != NULL)
		OF_prop_free(pins);
	if (cfg.function != NULL)
		OF_prop_free(cfg.function);
	return (rv);
}