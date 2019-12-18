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
struct acpi_ec {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ EC_FLAGS_CLEAR_ON_RESUME ; 
 int /*<<< orphan*/  __acpi_ec_enable_event (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_clear (struct acpi_ec*) ; 
 scalar_t__ acpi_ec_started (struct acpi_ec*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void acpi_ec_enable_event(struct acpi_ec *ec)
{
	unsigned long flags;

	spin_lock_irqsave(&ec->lock, flags);
	if (acpi_ec_started(ec))
		__acpi_ec_enable_event(ec);
	spin_unlock_irqrestore(&ec->lock, flags);

	/* Drain additional events if hardware requires that */
	if (EC_FLAGS_CLEAR_ON_RESUME)
		acpi_ec_clear(ec);
}