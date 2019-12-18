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
typedef  int /*<<< orphan*/  upd ;
typedef  size_t uint32_t ;
struct chipc_gpio_update {int dummy; } ;
struct chipc_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CC_GPIO_LOCK (struct chipc_gpio_softc*) ; 
 int /*<<< orphan*/  CC_GPIO_UNLOCK (struct chipc_gpio_softc*) ; 
 int /*<<< orphan*/  CC_GPIO_VALID_PINS (size_t,size_t) ; 
 int EINVAL ; 
 size_t GPIO_PIN_INPUT ; 
 size_t GPIO_PIN_OUTPUT ; 
 int chipc_gpio_commit_update (struct chipc_gpio_softc*,struct chipc_gpio_update*) ; 
 int chipc_gpio_pin_update (struct chipc_gpio_softc*,struct chipc_gpio_update*,size_t,size_t) ; 
 struct chipc_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct chipc_gpio_update*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
chipc_gpio_pin_config_32(device_t dev, uint32_t first_pin, uint32_t num_pins,
    uint32_t *pin_flags)
{
	struct chipc_gpio_softc		*sc;
	struct chipc_gpio_update	 upd;
	int				 error;
	
	sc = device_get_softc(dev);

	if (!CC_GPIO_VALID_PINS(first_pin, num_pins))
		return (EINVAL);

	/* Produce an update descriptor */
	memset(&upd, 0, sizeof(upd));
	for (uint32_t i = 0; i < num_pins; i++) {
		uint32_t pin, flags;

		pin = first_pin + i;
		flags = pin_flags[i];

		/* As per the gpio_config_32 API documentation, any pins for
		 * which neither GPIO_PIN_OUTPUT or GPIO_PIN_INPUT are set
		 * should be ignored and left unmodified */
		if ((flags & (GPIO_PIN_OUTPUT|GPIO_PIN_INPUT)) == 0)
			continue;

		if ((error = chipc_gpio_pin_update(sc, &upd, pin, flags)))
			return (error);
	}

	/* Commit the update */
	CC_GPIO_LOCK(sc);
	error = chipc_gpio_commit_update(sc, &upd);
	CC_GPIO_UNLOCK(sc);

	return (error);
}