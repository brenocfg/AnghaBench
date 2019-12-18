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
typedef  scalar_t__ uint32_t ;
struct ti_gpio_softc {int dummy; } ;
struct ti_gpio_irqsrc {scalar_t__ tgi_mode; int /*<<< orphan*/  tgi_mask; } ;

/* Variables and functions */
 scalar_t__ GPIO_INTR_EDGE_BOTH ; 
 scalar_t__ GPIO_INTR_EDGE_FALLING ; 
 scalar_t__ GPIO_INTR_EDGE_RISING ; 
 scalar_t__ GPIO_INTR_LEVEL_HIGH ; 
 scalar_t__ GPIO_INTR_LEVEL_LOW ; 
 int /*<<< orphan*/  TI_GPIO_FALLINGDETECT ; 
 int /*<<< orphan*/  TI_GPIO_LEVELDETECT0 ; 
 int /*<<< orphan*/  TI_GPIO_LEVELDETECT1 ; 
 int /*<<< orphan*/  TI_GPIO_LOCK (struct ti_gpio_softc*) ; 
 int /*<<< orphan*/  TI_GPIO_RISINGDETECT ; 
 int /*<<< orphan*/  TI_GPIO_UNLOCK (struct ti_gpio_softc*) ; 
 int /*<<< orphan*/  ti_gpio_rwreg_modify (struct ti_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ti_gpio_pic_config_intr(struct ti_gpio_softc *sc, struct ti_gpio_irqsrc *tgi,
    uint32_t mode)
{

	TI_GPIO_LOCK(sc);
	ti_gpio_rwreg_modify(sc, TI_GPIO_RISINGDETECT, tgi->tgi_mask,
	    mode == GPIO_INTR_EDGE_RISING || mode == GPIO_INTR_EDGE_BOTH);
	ti_gpio_rwreg_modify(sc, TI_GPIO_FALLINGDETECT, tgi->tgi_mask,
	    mode == GPIO_INTR_EDGE_FALLING || mode == GPIO_INTR_EDGE_BOTH);
	ti_gpio_rwreg_modify(sc, TI_GPIO_LEVELDETECT1, tgi->tgi_mask,
	    mode == GPIO_INTR_LEVEL_HIGH);
	ti_gpio_rwreg_modify(sc, TI_GPIO_LEVELDETECT0, tgi->tgi_mask,
	    mode == GPIO_INTR_LEVEL_LOW);
	tgi->tgi_mode = mode;
	TI_GPIO_UNLOCK(sc);
}