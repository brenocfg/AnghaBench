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
struct ti_gpio_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TI_GPIO_IRQSTATUS_CLR_0 ; 
 int /*<<< orphan*/  TI_GPIO_IRQSTATUS_CLR_1 ; 
 int /*<<< orphan*/  ti_gpio_write_4 (struct ti_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ti_gpio_intr_clr(struct ti_gpio_softc *sc, uint32_t mask)
{

	/* We clear both set of registers. */
	ti_gpio_write_4(sc, TI_GPIO_IRQSTATUS_CLR_0, mask);
	ti_gpio_write_4(sc, TI_GPIO_IRQSTATUS_CLR_1, mask);
}