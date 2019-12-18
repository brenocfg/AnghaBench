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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int __acpi_register_gsi (struct device*,int /*<<< orphan*/ ,int,int) ; 

int acpi_register_gsi(struct device *dev, u32 gsi, int trigger, int polarity)
{
	return __acpi_register_gsi(dev, gsi, trigger, polarity);
}