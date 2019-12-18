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

/* Variables and functions */
 int /*<<< orphan*/  AMDGPIO_LOCK (struct amdgpio_softc*) ; 
 int AMDGPIO_PIN_REGISTER (int) ; 
 int /*<<< orphan*/  AMDGPIO_UNLOCK (struct amdgpio_softc*) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTPUT_ENABLE_OFF ; 
 int amdgpio_read_4 (struct amdgpio_softc*,int) ; 

__attribute__((used)) static bool
amdgpio_is_pin_output(struct amdgpio_softc *sc, uint32_t pin)
{
	uint32_t reg, val;
	bool ret;

	/* Get the current pin state */
	AMDGPIO_LOCK(sc);

	reg = AMDGPIO_PIN_REGISTER(pin);
	val = amdgpio_read_4(sc, reg);

	if (val & BIT(OUTPUT_ENABLE_OFF))
		ret = true;
	else
		ret = false;

	AMDGPIO_UNLOCK(sc);

	return (ret);
}