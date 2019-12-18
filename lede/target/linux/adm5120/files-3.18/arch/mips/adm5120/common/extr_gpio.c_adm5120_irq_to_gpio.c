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

/* Variables and functions */
 int ADM5120_GPIO_PIN2 ; 
 int ADM5120_GPIO_PIN4 ; 
#define  ADM5120_IRQ_GPIO2 129 
#define  ADM5120_IRQ_GPIO4 128 
 int EINVAL ; 

int adm5120_irq_to_gpio(unsigned irq)
{
	int ret;

	switch (irq) {
	case ADM5120_IRQ_GPIO2:
		ret = ADM5120_GPIO_PIN2;
		break;
	case ADM5120_IRQ_GPIO4:
		ret = ADM5120_GPIO_PIN4;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}