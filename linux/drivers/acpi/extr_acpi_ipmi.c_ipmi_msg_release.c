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
struct acpi_ipmi_msg {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ipmi_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_ipmi_msg*) ; 

__attribute__((used)) static void ipmi_msg_release(struct acpi_ipmi_msg *tx_msg)
{
	acpi_ipmi_dev_put(tx_msg->device);
	kfree(tx_msg);
}