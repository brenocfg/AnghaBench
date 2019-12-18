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
struct bytgpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BYGPIO_PIN_REGISTER (struct bytgpio_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BYTGPIO_LOCK (struct bytgpio_softc*) ; 
 int /*<<< orphan*/  BYTGPIO_PAD_VAL ; 
 int BYTGPIO_PAD_VAL_I_INPUT_ENABLED ; 
 int BYTGPIO_PAD_VAL_I_OUTPUT_ENABLED ; 
 int /*<<< orphan*/  BYTGPIO_UNLOCK (struct bytgpio_softc*) ; 
 int EINVAL ; 
 int GPIO_PIN_INPUT ; 
 int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  bytgpio_pad_is_gpio (struct bytgpio_softc*,int) ; 
 int bytgpio_read_4 (struct bytgpio_softc*,int) ; 
 scalar_t__ bytgpio_valid_pin (struct bytgpio_softc*,int) ; 
 struct bytgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bytgpio_pin_getflags(device_t dev, uint32_t pin, uint32_t *flags)
{
	struct bytgpio_softc *sc;
	uint32_t reg, val;

	sc = device_get_softc(dev);
	if (bytgpio_valid_pin(sc, pin) != 0)
		return (EINVAL);

	*flags = 0;
	if (!bytgpio_pad_is_gpio(sc, pin))
		return (0);

	/* Get the current pin state */
	BYTGPIO_LOCK(sc);
	reg = BYGPIO_PIN_REGISTER(sc, pin, BYTGPIO_PAD_VAL);
	val = bytgpio_read_4(sc, reg);
	if ((val & BYTGPIO_PAD_VAL_I_OUTPUT_ENABLED) == 0)
		*flags |= GPIO_PIN_OUTPUT;
	/*
	 * this bit can be cleared to read current output value
	 * sou output bit takes precedense
	 */
	else if ((val & BYTGPIO_PAD_VAL_I_INPUT_ENABLED) == 0)
		*flags |= GPIO_PIN_INPUT;
	BYTGPIO_UNLOCK(sc);

	return (0);
}