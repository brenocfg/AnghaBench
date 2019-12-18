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
struct brcmstb_gpio_priv {int parent_wake_irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 

__attribute__((used)) static irqreturn_t brcmstb_gpio_wake_irq_handler(int irq, void *data)
{
	struct brcmstb_gpio_priv *priv = data;

	if (!priv || irq != priv->parent_wake_irq)
		return IRQ_NONE;

	/* Nothing to do */
	return IRQ_HANDLED;
}