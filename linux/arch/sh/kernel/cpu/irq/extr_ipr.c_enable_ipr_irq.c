#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int dummy; } ;
struct ipr_data {size_t ipr_idx; int priority; int shift; } ;
struct TYPE_2__ {unsigned long* ipr_offsets; } ;

/* Variables and functions */
 int __raw_readw (unsigned long) ; 
 int /*<<< orphan*/  __raw_writew (int,unsigned long) ; 
 TYPE_1__* get_ipr_desc (struct irq_data*) ; 
 struct ipr_data* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void enable_ipr_irq(struct irq_data *data)
{
	struct ipr_data *p = irq_data_get_irq_chip_data(data);
	unsigned long addr = get_ipr_desc(data)->ipr_offsets[p->ipr_idx];
	/* Set priority in IPR back to original value */
	__raw_writew(__raw_readw(addr) | (p->priority << p->shift), addr);
}