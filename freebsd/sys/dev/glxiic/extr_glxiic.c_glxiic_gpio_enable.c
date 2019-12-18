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
struct glxiic_softc {int /*<<< orphan*/  gpio_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLXIIC_GPIOL_IN_AUX1_SEL ; 
 int /*<<< orphan*/  GLXIIC_GPIOL_OUT_AUX1_SEL ; 
 int /*<<< orphan*/  GLXIIC_GPIO_14_15_ENABLE ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
glxiic_gpio_enable(struct glxiic_softc *sc)
{

	bus_write_4(sc->gpio_res, GLXIIC_GPIOL_IN_AUX1_SEL,
	    GLXIIC_GPIO_14_15_ENABLE);
	bus_write_4(sc->gpio_res, GLXIIC_GPIOL_OUT_AUX1_SEL,
	    GLXIIC_GPIO_14_15_ENABLE);
}