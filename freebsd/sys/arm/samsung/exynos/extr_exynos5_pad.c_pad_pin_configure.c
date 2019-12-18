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
struct pad_softc {int dummy; } ;
struct gpio_pin {unsigned int gp_flags; int /*<<< orphan*/  gp_pin; } ;
struct gpio_bank {int con; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_LOCK (struct pad_softc*) ; 
 unsigned int GPIO_PIN_INPUT ; 
 unsigned int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct pad_softc*) ; 
 int PIN_OUT ; 
 int READ4 (struct pad_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE4 (struct pad_softc*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ get_bank (struct pad_softc*,int /*<<< orphan*/ ,struct gpio_bank*,int*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void
pad_pin_configure(struct pad_softc *sc, struct gpio_pin *pin,
    unsigned int flags)
{
	struct gpio_bank bank;
	int pin_shift;
	int reg;

	GPIO_LOCK(sc);

	/*
	 * Manage input/output
	 */
	if (flags & (GPIO_PIN_INPUT|GPIO_PIN_OUTPUT)) {
		pin->gp_flags &= ~(GPIO_PIN_INPUT|GPIO_PIN_OUTPUT);

		if (get_bank(sc, pin->gp_pin, &bank, &pin_shift) != 0)
			return;

		pin_shift *= 4;

#if 0
		printf("bank is 0x%08x pin_shift %d\n", bank.con, pin_shift);
#endif

		if (flags & GPIO_PIN_OUTPUT) {
			pin->gp_flags |= GPIO_PIN_OUTPUT;
			reg = READ4(sc, bank.port, bank.con);
			reg &= ~(0xf << pin_shift);
			reg |= (PIN_OUT << pin_shift);
			WRITE4(sc, bank.port, bank.con, reg);
		} else {
			pin->gp_flags |= GPIO_PIN_INPUT;
			reg = READ4(sc, bank.port, bank.con);
			reg &= ~(0xf << pin_shift);
			WRITE4(sc, bank.port, bank.con, reg);
		}
	}

	GPIO_UNLOCK(sc);
}