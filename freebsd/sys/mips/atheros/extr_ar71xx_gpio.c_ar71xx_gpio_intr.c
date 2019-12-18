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
struct ar71xx_gpio_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_LOCK (struct ar71xx_gpio_softc*) ; 
 int /*<<< orphan*/  GPIO_UNLOCK (struct ar71xx_gpio_softc*) ; 

__attribute__((used)) static void
ar71xx_gpio_intr(void *arg)
{
	struct ar71xx_gpio_softc *sc = arg;
	GPIO_LOCK(sc);
	/* TODO: something useful */
	GPIO_UNLOCK(sc);
}