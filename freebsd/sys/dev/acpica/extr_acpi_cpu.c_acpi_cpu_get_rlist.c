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
struct resource_list {int dummy; } ;
struct acpi_cpu_device {struct resource_list ad_rl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct acpi_cpu_device* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource_list *
acpi_cpu_get_rlist(device_t dev, device_t child)
{
    struct acpi_cpu_device *ad;

    ad = device_get_ivars(child);
    if (ad == NULL)
	return (NULL);
    return (&ad->ad_rl);
}