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
struct gpio_match {size_t ctrl; int /*<<< orphan*/ * name; } ;
struct aoagpio_softc {size_t ctrl; char detect_active; int /*<<< orphan*/ * i2s; scalar_t__ level; int /*<<< orphan*/  dev; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bname ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int GPIO_CTRL_EXTINT_SET ; 
 int OF_getprop (int,char*,char*,int) ; 
 int /*<<< orphan*/  aoagpio_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 struct aoagpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct gpio_match* gpio_controls ; 
 struct aoagpio_softc** gpio_ctrls ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aoagpio_probe(device_t gpio)
{
	phandle_t	 	 node;
	char			 bname[32];
	const char 		*name;
	struct gpio_match	*m;
	struct aoagpio_softc	*sc;

	node = ofw_bus_get_node(gpio);
	if (node == 0 || node == -1)
		return (EINVAL);

	bzero(bname, sizeof(bname));
	if (OF_getprop(node, "audio-gpio", bname, sizeof(bname)) > 2)
		name = bname;
	else
		name = ofw_bus_get_name(gpio);

	/* Try to find a match. */
	for (m = gpio_controls; m->name != NULL; m++) {
		if (strcmp(name, m->name) == 0) {
			sc = device_get_softc(gpio);
			gpio_ctrls[m->ctrl] = sc;
			sc->dev = gpio;
			sc->ctrl = m->ctrl;
			sc->level = 0;
			sc->detect_active = 0;
			sc->i2s = NULL;

			OF_getprop(node, "audio-gpio-active-state", 
				&sc->detect_active, sizeof(sc->detect_active));

			if ((1 << m->ctrl) & GPIO_CTRL_EXTINT_SET)
				aoagpio_int(gpio);

			device_set_desc(gpio, m->name);
			device_quiet(gpio);
			return (0);
		}
	}

	return (ENXIO);
}