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
struct ckb_softc {void* gpio; void* cols; void* rows; int /*<<< orphan*/  dev; } ;
typedef  int phandle_t ;
typedef  void* pcell_t ;

/* Variables and functions */
 int ENXIO ; 
 int KEYMAP_LEN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,void**,int) ; 
 int OF_getproplen (int,char*) ; 
 scalar_t__ OF_hasprop (int,char*) ; 
 void** default_keymap ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void**,int /*<<< orphan*/ ) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int parse_keymap (struct ckb_softc*,void**,int) ; 
 int read_keymap (int,char const*,void***,int*) ; 

__attribute__((used)) static int
parse_dts(struct ckb_softc *sc)
{
	phandle_t node;
	pcell_t dts_value;
	pcell_t *keymap;
	int len, ret;
	const char *keymap_prop = NULL;

	if ((node = ofw_bus_get_node(sc->dev)) == -1)
		return (ENXIO);

	if ((len = OF_getproplen(node, "google,key-rows")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "google,key-rows", &dts_value, len);
	sc->rows = dts_value;

	if ((len = OF_getproplen(node, "google,key-columns")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "google,key-columns", &dts_value, len);
	sc->cols = dts_value;

	if ((len = OF_getproplen(node, "freebsd,intr-gpio")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "freebsd,intr-gpio", &dts_value, len);
	sc->gpio = dts_value;

	if (OF_hasprop(node, "freebsd,keymap")) {
		keymap_prop = "freebsd,keymap";
		device_printf(sc->dev, "using FreeBSD-specific keymap from FDT\n");
	} else if (OF_hasprop(node, "linux,keymap")) {
		keymap_prop = "linux,keymap";
		device_printf(sc->dev, "using Linux keymap from FDT\n");
	} else {
		device_printf(sc->dev, "using built-in keymap\n");
	}

	if (keymap_prop != NULL) {
		if ((ret = read_keymap(node, keymap_prop, &keymap, &len))) {
			device_printf(sc->dev,
			     "failed to read keymap from FDT: %d\n", ret);
			return (ret);
		}
		ret = parse_keymap(sc, keymap, len);
		free(keymap, M_DEVBUF);
		if (ret) {
			return (ret);
		}
	} else {
		if ((ret = parse_keymap(sc, default_keymap, KEYMAP_LEN))) {
			return (ret);
		}
	}

	if ((sc->rows == 0) || (sc->cols == 0) || (sc->gpio == 0))
		return (ENXIO);

	return (0);
}