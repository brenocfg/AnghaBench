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
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct gpiobacklight_softc {int sc_brightness; int /*<<< orphan*/  sc_oid; int /*<<< orphan*/ * sc_pin; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 scalar_t__ OF_hasprop (int,char*) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct gpiobacklight_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct gpiobacklight_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_pin_get_by_ofw_idx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  gpio_pin_setflags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobacklight_sysctl ; 
 int /*<<< orphan*/  gpiobacklight_update_brightness (struct gpiobacklight_softc*) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpiobacklight_attach(device_t dev)
{
	struct gpiobacklight_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree;
	phandle_t node;

	sc = device_get_softc(dev);

	if ((node = ofw_bus_get_node(dev)) == -1)
		return (ENXIO);

	if (OF_hasprop(node, "default-on"))
		sc->sc_brightness = true;
	else
		sc->sc_brightness = false;

	gpio_pin_get_by_ofw_idx(dev, node, 0, &sc->sc_pin);
	if (sc->sc_pin == NULL) {
		device_printf(dev, "failed to map GPIO pin\n");
		return (ENXIO);
	}

	gpio_pin_setflags(sc->sc_pin, GPIO_PIN_OUTPUT);

	gpiobacklight_update_brightness(sc);

	/* Init backlight interface */
	ctx = device_get_sysctl_ctx(dev);
	tree = device_get_sysctl_tree(dev);
	sc->sc_oid = SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "brightness", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
	    gpiobacklight_sysctl, "I", "backlight brightness");

	return (0);
}