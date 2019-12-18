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
struct spider_pic {int dummy; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct spider_pic* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static struct spider_pic *spider_irq_data_to_pic(struct irq_data *d)
{
	return irq_data_get_irq_chip_data(d);
}