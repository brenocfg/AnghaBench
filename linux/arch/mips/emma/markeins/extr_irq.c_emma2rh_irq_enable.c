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
typedef  int u32 ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 unsigned int EMMA2RH_BHIF_INT_EN_0 ; 
 unsigned int EMMA2RH_BHIF_INT_EN_1 ; 
 unsigned int EMMA2RH_IRQ_BASE ; 
 int emma2rh_in32 (int) ; 
 int /*<<< orphan*/  emma2rh_out32 (int,int) ; 

__attribute__((used)) static void emma2rh_irq_enable(struct irq_data *d)
{
	unsigned int irq = d->irq - EMMA2RH_IRQ_BASE;
	u32 reg_value, reg_bitmask, reg_index;

	reg_index = EMMA2RH_BHIF_INT_EN_0 +
		    (EMMA2RH_BHIF_INT_EN_1 - EMMA2RH_BHIF_INT_EN_0) * (irq / 32);
	reg_value = emma2rh_in32(reg_index);
	reg_bitmask = 0x1 << (irq % 32);
	emma2rh_out32(reg_index, reg_value | reg_bitmask);
}