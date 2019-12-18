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
struct TYPE_3__ {int base; } ;
struct brcmstb_gpio_bank {TYPE_2__* parent_priv; TYPE_1__ gc; } ;
typedef  int irq_hw_number_t ;
struct TYPE_4__ {int gpio_base; } ;

/* Variables and functions */

__attribute__((used)) static int brcmstb_gpio_hwirq_to_offset(irq_hw_number_t hwirq,
					struct brcmstb_gpio_bank *bank)
{
	return hwirq - (bank->gc.base - bank->parent_priv->gpio_base);
}