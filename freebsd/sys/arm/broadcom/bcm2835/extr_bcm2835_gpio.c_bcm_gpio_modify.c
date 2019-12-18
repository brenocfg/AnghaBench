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
struct bcm_gpio_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GPIO_CLEAR_BITS (struct bcm_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_SET_BITS (struct bcm_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
bcm_gpio_modify(struct bcm_gpio_softc *sc, uint32_t reg, uint32_t mask,
    bool set_bits)
{

	if (set_bits)
		BCM_GPIO_SET_BITS(sc, reg, mask);
	else
		BCM_GPIO_CLEAR_BITS(sc, reg, mask);
}