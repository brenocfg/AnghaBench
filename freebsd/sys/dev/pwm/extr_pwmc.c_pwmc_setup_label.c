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
struct pwmc_softc {int /*<<< orphan*/  cdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_prop_free (void*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_dev_alias (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 

__attribute__((used)) static void
pwmc_setup_label(struct pwmc_softc *sc)
{
	const char *hintlabel;
#ifdef FDT
	void *label;

	if (OF_getprop_alloc(ofw_bus_get_node(sc->dev), "label", &label) > 0) {
		make_dev_alias(sc->cdev, "pwm/%s", (char *)label);
		OF_prop_free(label);
	}
#endif

	if (resource_string_value(device_get_name(sc->dev),
	    device_get_unit(sc->dev), "label", &hintlabel) == 0) {
		make_dev_alias(sc->cdev, "pwm/%s", hintlabel);
	}
}