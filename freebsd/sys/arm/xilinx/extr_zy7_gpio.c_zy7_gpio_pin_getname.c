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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EMIO_PIN ; 
 int GPIOMAXNAME ; 
 scalar_t__ NUM_MIO_PINS ; 
 int /*<<< orphan*/  VALID_PIN (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 

__attribute__((used)) static int
zy7_gpio_pin_getname(device_t dev, uint32_t pin, char *name)
{

	if (!VALID_PIN(pin))
		return (EINVAL);

	if (pin < NUM_MIO_PINS) {
		snprintf(name, GPIOMAXNAME, "MIO_%d", pin);
		name[GPIOMAXNAME - 1] = '\0';
	} else {
		snprintf(name, GPIOMAXNAME, "EMIO_%d", pin - EMIO_PIN);
		name[GPIOMAXNAME - 1] = '\0';
	}

	return (0);
}