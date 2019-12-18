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
struct acpi_ec {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_FLAGS_QUERY_ENABLED ; 
 int /*<<< orphan*/  advance_transaction (struct acpi_ec*) ; 
 int /*<<< orphan*/  ec_log_drv (char*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __acpi_ec_enable_event(struct acpi_ec *ec)
{
	if (!test_and_set_bit(EC_FLAGS_QUERY_ENABLED, &ec->flags))
		ec_log_drv("event unblocked");
	/*
	 * Unconditionally invoke this once after enabling the event
	 * handling mechanism to detect the pending events.
	 */
	advance_transaction(ec);
}