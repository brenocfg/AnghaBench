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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 scalar_t__ pica ; 
 scalar_t__ picb ; 

void apollo_irq_shutdown(struct irq_data *data)
{
	unsigned int irq = data->irq;

	if (irq < 8)
		*(volatile unsigned char *)(pica+1) |= (1 << irq);
	else
		*(volatile unsigned char *)(picb+1) |= (1 << (irq - 8));
}