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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ ACPI_ACTIVE_LOW ; 
 scalar_t__ ACPI_LEVEL_SENSITIVE ; 
 scalar_t__ ACPI_SHARED ; 
 unsigned long IORESOURCE_IRQ ; 
 unsigned long IORESOURCE_IRQ_HIGHEDGE ; 
 unsigned long IORESOURCE_IRQ_HIGHLEVEL ; 
 unsigned long IORESOURCE_IRQ_LOWEDGE ; 
 unsigned long IORESOURCE_IRQ_LOWLEVEL ; 
 unsigned long IORESOURCE_IRQ_SHAREABLE ; 

unsigned long acpi_dev_irq_flags(u8 triggering, u8 polarity, u8 shareable)
{
	unsigned long flags;

	if (triggering == ACPI_LEVEL_SENSITIVE)
		flags = polarity == ACPI_ACTIVE_LOW ?
			IORESOURCE_IRQ_LOWLEVEL : IORESOURCE_IRQ_HIGHLEVEL;
	else
		flags = polarity == ACPI_ACTIVE_LOW ?
			IORESOURCE_IRQ_LOWEDGE : IORESOURCE_IRQ_HIGHEDGE;

	if (shareable == ACPI_SHARED)
		flags |= IORESOURCE_IRQ_SHAREABLE;

	return flags | IORESOURCE_IRQ;
}