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
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct adnp {int reg_shift; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  i2c_lock; int /*<<< orphan*/ * irq_enable; } ;

/* Variables and functions */
 scalar_t__ GPIO_IER (struct adnp*) ; 
 int /*<<< orphan*/  adnp_write (struct adnp*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct adnp* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adnp_irq_bus_unlock(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct adnp *adnp = gpiochip_get_data(gc);
	unsigned int num_regs = 1 << adnp->reg_shift, i;

	mutex_lock(&adnp->i2c_lock);

	for (i = 0; i < num_regs; i++)
		adnp_write(adnp, GPIO_IER(adnp) + i, adnp->irq_enable[i]);

	mutex_unlock(&adnp->i2c_lock);
	mutex_unlock(&adnp->irq_lock);
}