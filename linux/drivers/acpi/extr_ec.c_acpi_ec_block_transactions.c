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
struct acpi_ec {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ec_stop (struct acpi_ec*,int) ; 
 struct acpi_ec* first_ec ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void acpi_ec_block_transactions(void)
{
	struct acpi_ec *ec = first_ec;

	if (!ec)
		return;

	mutex_lock(&ec->mutex);
	/* Prevent transactions from being carried out */
	acpi_ec_stop(ec, true);
	mutex_unlock(&ec->mutex);
}