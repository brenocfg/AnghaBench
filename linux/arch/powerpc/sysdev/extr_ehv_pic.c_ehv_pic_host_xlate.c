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
typedef  size_t u32 ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
typedef  size_t irq_hw_number_t ;

/* Variables and functions */
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 size_t const IRQ_TYPE_MPIC_DIRECT ; 
 unsigned int IRQ_TYPE_NONE ; 
 size_t* hwirq_intspec ; 

__attribute__((used)) static int ehv_pic_host_xlate(struct irq_domain *h, struct device_node *ct,
			   const u32 *intspec, unsigned int intsize,
			   irq_hw_number_t *out_hwirq, unsigned int *out_flags)

{
	/*
	 * interrupt sense values coming from the guest device tree
	 * interrupt specifiers can have four possible sense and
	 * level encoding information and they need to
	 * be translated between firmware type & linux type.
	 */

	static unsigned char map_of_senses_to_linux_irqtype[4] = {
		IRQ_TYPE_EDGE_FALLING,
		IRQ_TYPE_EDGE_RISING,
		IRQ_TYPE_LEVEL_LOW,
		IRQ_TYPE_LEVEL_HIGH,
	};

	*out_hwirq = intspec[0];
	if (intsize > 1) {
		hwirq_intspec[intspec[0]] = intspec[1];
		*out_flags = map_of_senses_to_linux_irqtype[intspec[1] &
							~IRQ_TYPE_MPIC_DIRECT];
	} else {
		*out_flags = IRQ_TYPE_NONE;
	}

	return 0;
}