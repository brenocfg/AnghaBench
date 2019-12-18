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
#define  ACPI_ACTIVE_BOTH 130 
#define  ACPI_ACTIVE_HIGH 129 
#define  ACPI_ACTIVE_LOW 128 
 int ACPI_EDGE_SENSITIVE ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_NONE ; 

unsigned int acpi_dev_get_irq_type(int triggering, int polarity)
{
	switch (polarity) {
	case ACPI_ACTIVE_LOW:
		return triggering == ACPI_EDGE_SENSITIVE ?
		       IRQ_TYPE_EDGE_FALLING :
		       IRQ_TYPE_LEVEL_LOW;
	case ACPI_ACTIVE_HIGH:
		return triggering == ACPI_EDGE_SENSITIVE ?
		       IRQ_TYPE_EDGE_RISING :
		       IRQ_TYPE_LEVEL_HIGH;
	case ACPI_ACTIVE_BOTH:
		if (triggering == ACPI_EDGE_SENSITIVE)
			return IRQ_TYPE_EDGE_BOTH;
		/* fall through */
	default:
		return IRQ_TYPE_NONE;
	}
}