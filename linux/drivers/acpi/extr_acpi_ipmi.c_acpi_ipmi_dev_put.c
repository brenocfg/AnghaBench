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
struct acpi_ipmi_device {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipmi_dev_release_kref ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_ipmi_dev_put(struct acpi_ipmi_device *ipmi_device)
{
	kref_put(&ipmi_device->kref, ipmi_dev_release_kref);
}