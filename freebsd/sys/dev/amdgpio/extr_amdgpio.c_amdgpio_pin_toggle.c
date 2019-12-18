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
struct amdgpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPIO_LOCK (struct amdgpio_softc*) ; 
 int AMDGPIO_PIN_REGISTER (int) ; 
 int /*<<< orphan*/  AMDGPIO_UNLOCK (struct amdgpio_softc*) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUTPUT_VALUE_OFF ; 
 int /*<<< orphan*/  amdgpio_is_pin_output (struct amdgpio_softc*,int) ; 
 int amdgpio_read_4 (struct amdgpio_softc*,int) ; 
 int /*<<< orphan*/  amdgpio_valid_pin (struct amdgpio_softc*,int) ; 
 int /*<<< orphan*/  amdgpio_write_4 (struct amdgpio_softc*,int,int) ; 
 struct amdgpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int,...) ; 

__attribute__((used)) static int
amdgpio_pin_toggle(device_t dev, uint32_t pin)
{
	struct amdgpio_softc *sc;
	uint32_t reg, val;

	sc = device_get_softc(dev);

	dprintf("pin %d\n", pin);
	if (!amdgpio_valid_pin(sc, pin))
		return (EINVAL);

	if (!amdgpio_is_pin_output(sc, pin))
		return (EINVAL);

	/* Toggle the pin */
	AMDGPIO_LOCK(sc);

	reg = AMDGPIO_PIN_REGISTER(pin);
	val = amdgpio_read_4(sc, reg);
	dprintf("pin %d value before 0x%x\n", pin, val);
	val = val ^ BIT(OUTPUT_VALUE_OFF);
	dprintf("pin %d value after 0x%x\n", pin, val);
	amdgpio_write_4(sc, reg, val);

	AMDGPIO_UNLOCK(sc);

	return (0);
}