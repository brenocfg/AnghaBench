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
struct platform_device {int dummy; } ;
struct neponset_drvdata {int /*<<< orphan*/  base; int /*<<< orphan*/  irq_base; int /*<<< orphan*/  smc91x; int /*<<< orphan*/  sa1111; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEP_IRQ_NR ; 
 int /*<<< orphan*/  gpiod_remove_lookup_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_free_descs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct neponset_drvdata*) ; 
 int /*<<< orphan*/ * nep ; 
 int /*<<< orphan*/  neponset_pcmcia_table ; 
 int /*<<< orphan*/  neponset_uart1_gpio_table ; 
 int /*<<< orphan*/  neponset_uart3_gpio_table ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct neponset_drvdata* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int neponset_remove(struct platform_device *dev)
{
	struct neponset_drvdata *d = platform_get_drvdata(dev);
	int irq = platform_get_irq(dev, 0);

	if (!IS_ERR(d->sa1111))
		platform_device_unregister(d->sa1111);
	if (!IS_ERR(d->smc91x))
		platform_device_unregister(d->smc91x);

	gpiod_remove_lookup_table(&neponset_pcmcia_table);
	gpiod_remove_lookup_table(&neponset_uart3_gpio_table);
	gpiod_remove_lookup_table(&neponset_uart1_gpio_table);

	irq_set_chained_handler(irq, NULL);
	irq_free_descs(d->irq_base, NEP_IRQ_NR);
	nep = NULL;
	iounmap(d->base);
	kfree(d);

	return 0;
}