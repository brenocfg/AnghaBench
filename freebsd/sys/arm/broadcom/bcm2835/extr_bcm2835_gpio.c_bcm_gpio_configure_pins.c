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
typedef  int uint32_t ;
struct bcm_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  function ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  BCM2835_PUD_DOWN 130 
#define  BCM2835_PUD_OFF 129 
#define  BCM2835_PUD_UP 128 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  GPIO_PIN_PULLDOWN ; 
 int /*<<< orphan*/  GPIO_PIN_PULLUP ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_getprop (int /*<<< orphan*/ ,char*,char**,int) ; 
 int /*<<< orphan*/  OF_node_from_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_prop_free (int*) ; 
 int /*<<< orphan*/  bcm_gpio_pin_setflags (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_gpio_set_alternate (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ bootverbose ; 
 struct bcm_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
bcm_gpio_configure_pins(device_t dev, phandle_t cfgxref)
{
	phandle_t cfgnode;
	int i, pintuples, pulltuples;
	uint32_t pin;
	uint32_t *pins;
	uint32_t *pulls;
	uint32_t function;
	static struct bcm_gpio_softc *sc;

	sc = device_get_softc(dev);
	cfgnode = OF_node_from_xref(cfgxref);

	pins = NULL;
	pintuples = OF_getencprop_alloc_multi(cfgnode, "brcm,pins",
	    sizeof(*pins), (void **)&pins);

	char name[32];
	OF_getprop(cfgnode, "name", &name, sizeof(name));

	if (pintuples < 0)
		return (ENOENT);

	if (pintuples == 0)
		return (0); /* Empty property is not an error. */

	if (OF_getencprop(cfgnode, "brcm,function", &function,
	    sizeof(function)) <= 0) {
		OF_prop_free(pins);
		return (EINVAL);
	}

	pulls = NULL;
	pulltuples = OF_getencprop_alloc_multi(cfgnode, "brcm,pull",
	    sizeof(*pulls), (void **)&pulls);

	if ((pulls != NULL) && (pulltuples != pintuples)) {
		OF_prop_free(pins);
		OF_prop_free(pulls);
		return (EINVAL);
	}

	for (i = 0; i < pintuples; i++) {
		pin = pins[i];
		bcm_gpio_set_alternate(dev, pin, function);
		if (bootverbose)
			device_printf(dev, "set pin %d to func %d", pin, function);
		if (pulls) {
			if (bootverbose)
				printf(", pull %d", pulls[i]);
			switch (pulls[i]) {
			/* Convert to gpio(4) flags */
			case BCM2835_PUD_OFF:
				bcm_gpio_pin_setflags(dev, pin, 0);
				break;
			case BCM2835_PUD_UP:
				bcm_gpio_pin_setflags(dev, pin, GPIO_PIN_PULLUP);
				break;
			case BCM2835_PUD_DOWN:
				bcm_gpio_pin_setflags(dev, pin, GPIO_PIN_PULLDOWN);
				break;
			default:
				printf("%s: invalid pull value for pin %d: %d\n",
				    name, pin, pulls[i]);
			}
		}
		if (bootverbose)
			printf("\n");
	}

	OF_prop_free(pins);
	if (pulls)
		OF_prop_free(pulls);

	return (0);
}