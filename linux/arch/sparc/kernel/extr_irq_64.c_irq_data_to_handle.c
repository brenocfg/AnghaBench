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
struct irq_handler_data {unsigned int dev_handle; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct irq_handler_data* irq_data_get_irq_handler_data (struct irq_data*) ; 

__attribute__((used)) static inline unsigned int irq_data_to_handle(struct irq_data *data)
{
	struct irq_handler_data *ihd = irq_data_get_irq_handler_data(data);

	return ihd->dev_handle;
}