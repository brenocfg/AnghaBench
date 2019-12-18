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
struct max14577_muic_info {int irq_adc; int irq_chg; } ;

/* Variables and functions */
#define  MAX77836_IRQ_INT1_ADC1K 129 
#define  MAX77836_IRQ_INT2_VIDRM 128 
 scalar_t__ max14577_parse_irq (struct max14577_muic_info*,int) ; 

__attribute__((used)) static int max77836_parse_irq(struct max14577_muic_info *info, int irq_type)
{
	/* First check common max14577 interrupts */
	if (max14577_parse_irq(info, irq_type))
		return 1;

	switch (irq_type) {
	case MAX77836_IRQ_INT1_ADC1K:
		info->irq_adc = true;
		return 1;
	case MAX77836_IRQ_INT2_VIDRM:
		/* Handle charger accessory */
		info->irq_chg = true;
		return 1;
	default:
		return 0;
	}
}