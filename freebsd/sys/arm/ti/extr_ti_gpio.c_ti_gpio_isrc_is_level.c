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
struct ti_gpio_irqsrc {scalar_t__ tgi_mode; } ;

/* Variables and functions */
 scalar_t__ GPIO_INTR_LEVEL_HIGH ; 
 scalar_t__ GPIO_INTR_LEVEL_LOW ; 

__attribute__((used)) static inline bool
ti_gpio_isrc_is_level(struct ti_gpio_irqsrc *tgi)
{

	return (tgi->tgi_mode == GPIO_INTR_LEVEL_LOW ||
	    tgi->tgi_mode == GPIO_INTR_LEVEL_HIGH);
}