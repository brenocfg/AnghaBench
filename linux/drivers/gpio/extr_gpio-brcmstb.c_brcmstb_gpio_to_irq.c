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
struct gpio_chip {unsigned int base; } ;
struct brcmstb_gpio_priv {unsigned int gpio_base; int num_gpios; int /*<<< orphan*/  irq_domain; } ;

/* Variables and functions */
 int ENXIO ; 
 struct brcmstb_gpio_priv* brcmstb_gpio_gc_to_priv (struct gpio_chip*) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int brcmstb_gpio_to_irq(struct gpio_chip *gc, unsigned offset)
{
	struct brcmstb_gpio_priv *priv = brcmstb_gpio_gc_to_priv(gc);
	/* gc_offset is relative to this gpio_chip; want real offset */
	int hwirq = offset + (gc->base - priv->gpio_base);

	if (hwirq >= priv->num_gpios)
		return -ENXIO;
	return irq_create_mapping(priv->irq_domain, hwirq);
}