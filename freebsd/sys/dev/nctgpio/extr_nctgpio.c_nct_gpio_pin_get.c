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
typedef  int /*<<< orphan*/  uint32_t ;
struct nct_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_ASSERT_UNLOCKED (struct nct_softc*) ; 
 int /*<<< orphan*/  GPIO_LOCK (struct nct_softc*) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct nct_softc*) ; 
 int /*<<< orphan*/  NCT_IS_VALID_PIN (int /*<<< orphan*/ ) ; 
 struct nct_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct_read_pin (struct nct_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nct_gpio_pin_get(device_t dev, uint32_t pin_num, uint32_t *pin_value)
{
	struct nct_softc *sc;

	if (!NCT_IS_VALID_PIN(pin_num))
		return (EINVAL);

	sc = device_get_softc(dev);
	GPIO_ASSERT_UNLOCKED(sc);
	GPIO_LOCK(sc);
	*pin_value = nct_read_pin(sc, pin_num);
	GPIO_UNLOCK(sc);

	return (0);
}