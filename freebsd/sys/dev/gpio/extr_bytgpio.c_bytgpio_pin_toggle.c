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
 int BYTGPIO_PAD_VAL_LEVEL ; 
 int /*<<< orphan*/  BYTGPIO_UNLOCK (struct bytgpio_softc*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bytgpio_pad_is_gpio (struct bytgpio_softc*,int) ; 
 int bytgpio_read_4 (struct bytgpio_softc*,int) ; 
 scalar_t__ bytgpio_valid_pin (struct bytgpio_softc*,int) ; 
 int /*<<< orphan*/  bytgpio_write_4 (struct bytgpio_softc*,int,int) ; 
 struct bytgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bytgpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct bytgpio_softc *sc;
	uint32_t reg, val;

	sc = device_get_softc(dev);
	if (bytgpio_valid_pin(sc, pin) != 0)
		return (EINVAL);

	if (!bytgpio_pad_is_gpio(sc, pin))
		return (EINVAL);

	/* Toggle the pin */
	BYTGPIO_LOCK(sc);
	reg = BYGPIO_PIN_REGISTER(sc, pin, BYTGPIO_PAD_VAL);
	val = bytgpio_read_4(sc, reg);
	val = val ^ BYTGPIO_PAD_VAL_LEVEL;
	bytgpio_write_4(sc, reg, val);
	BYTGPIO_UNLOCK(sc);

	return (0);
}