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
struct acpi_ipmi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  user_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_ipmi_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipmi_dev_release(struct acpi_ipmi_device *ipmi_device)
{
	ipmi_destroy_user(ipmi_device->user_interface);
	put_device(ipmi_device->dev);
	kfree(ipmi_device);
}