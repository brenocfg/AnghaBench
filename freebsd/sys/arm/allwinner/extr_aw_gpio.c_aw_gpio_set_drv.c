#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct aw_gpio_softc {TYPE_2__* padconf; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct TYPE_3__ {size_t port; size_t pin; } ;

/* Variables and functions */
 size_t AW_GPIO_DRV_MASK ; 
 int /*<<< orphan*/  AW_GPIO_GP_DRV (size_t,size_t) ; 
 int /*<<< orphan*/  AW_GPIO_LOCK_ASSERT (struct aw_gpio_softc*) ; 
 size_t AW_GPIO_READ (struct aw_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AW_GPIO_WRITE (struct aw_gpio_softc*,int /*<<< orphan*/ ,size_t) ; 
 size_t aw_gpio_get_drv (struct aw_gpio_softc*,size_t) ; 

__attribute__((used)) static void
aw_gpio_set_drv(struct aw_gpio_softc *sc, uint32_t pin, uint32_t drive)
{
	uint32_t bank, offset, val;

	if (aw_gpio_get_drv(sc, pin) == drive)
		return;

	/* Must be called with lock held. */
	AW_GPIO_LOCK_ASSERT(sc);

	bank = sc->padconf->pins[pin].port;
	pin = sc->padconf->pins[pin].pin;
	offset = ((pin & 0x0f) << 1);

	val = AW_GPIO_READ(sc, AW_GPIO_GP_DRV(bank, pin >> 4));
	val &= ~(AW_GPIO_DRV_MASK << offset);
	val |= (drive << offset);
	AW_GPIO_WRITE(sc, AW_GPIO_GP_DRV(bank, pin >> 4), val);
}