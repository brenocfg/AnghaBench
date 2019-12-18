#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct nct_softc {TYPE_1__* pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  gp_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 int /*<<< orphan*/  GPIO_ASSERT_UNLOCKED (struct nct_softc*) ; 
 int /*<<< orphan*/  GPIO_LOCK (struct nct_softc*) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct nct_softc*) ; 
 int /*<<< orphan*/  NCT_IS_VALID_PIN (size_t) ; 
 struct nct_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nct_gpio_pin_getname(device_t dev, uint32_t pin_num, char *name)
{
	struct nct_softc *sc;

	if (!NCT_IS_VALID_PIN(pin_num))
		return (EINVAL);

	sc = device_get_softc(dev);
	GPIO_ASSERT_UNLOCKED(sc);
	GPIO_LOCK(sc);
	memcpy(name, sc->pins[pin_num].gp_name, GPIOMAXNAME);
	GPIO_UNLOCK(sc);

	return (0);
}