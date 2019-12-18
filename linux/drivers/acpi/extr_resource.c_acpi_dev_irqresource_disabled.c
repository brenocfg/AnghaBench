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
typedef  void* u32 ;
struct resource {int flags; void* end; void* start; } ;

/* Variables and functions */
 int IORESOURCE_DISABLED ; 
 int IORESOURCE_IRQ ; 
 int IORESOURCE_UNSET ; 

__attribute__((used)) static void acpi_dev_irqresource_disabled(struct resource *res, u32 gsi)
{
	res->start = gsi;
	res->end = gsi;
	res->flags = IORESOURCE_IRQ | IORESOURCE_DISABLED | IORESOURCE_UNSET;
}