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
struct as3722_softc {int /*<<< orphan*/  dev; } ;
struct as3722_pincfg {char* function; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int as3722_pinmux_config_node (struct as3722_softc*,char*,struct as3722_pincfg*) ; 
 int as3722_pinmux_read_node (struct as3722_softc*,int /*<<< orphan*/ ,struct as3722_pincfg*,char**,int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
as3722_pinmux_process_node(struct as3722_softc *sc, phandle_t node)
{
	struct as3722_pincfg cfg;
	char *pins, *pname;
	int i, len, lpins, rv;

	rv = as3722_pinmux_read_node(sc, node, &cfg, &pins, &lpins);
	if (rv != 0)
		return (rv);

	len = 0;
	pname = pins;
	do {
		i = strlen(pname) + 1;
		rv = as3722_pinmux_config_node(sc, pname, &cfg);
		if (rv != 0) {
			device_printf(sc->dev,
			    "Cannot configure pin: %s: %d\n", pname, rv);
		}
		len += i;
		pname += i;
	} while (len < lpins);

	if (pins != NULL)
		OF_prop_free(pins);
	if (cfg.function != NULL)
		OF_prop_free(cfg.function);

	return (rv);
}