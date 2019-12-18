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
struct irq_data {size_t irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAST_VA_PC104_IRQMASK ; 
 unsigned long __raw_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long* bast_pc104_irqmasks ; 

__attribute__((used)) static void
bast_pc104_unmask(struct irq_data *data)
{
	unsigned long temp;

	temp = __raw_readb(BAST_VA_PC104_IRQMASK);
	temp |= bast_pc104_irqmasks[data->irq];
	__raw_writeb(temp, BAST_VA_PC104_IRQMASK);
}