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
struct rcc_gpio_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCC_GPIO_LOCK (struct rcc_gpio_softc*) ; 
 int /*<<< orphan*/  RCC_GPIO_UNLOCK (struct rcc_gpio_softc*) ; 
 int /*<<< orphan*/  RCC_READ (struct rcc_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCC_WRITE (struct rcc_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rcc_gpio_modify_bits(struct rcc_gpio_softc *sc, uint32_t reg, uint32_t mask,
	uint32_t writebits)
{
	uint32_t value;

	RCC_GPIO_LOCK(sc);
	value = RCC_READ(sc, reg);
	value &= ~mask;
	value |= writebits;
	RCC_WRITE(sc, reg, value);
	RCC_GPIO_UNLOCK(sc);
}