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
 int /*<<< orphan*/  EC_FLAGS_STARTED ; 
 int acpi_ec_started (struct acpi_ec*) ; 
 scalar_t__ ec_freeze_events ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool acpi_ec_event_enabled(struct acpi_ec *ec)
{
	/*
	 * There is an OSPM early stage logic. During the early stages
	 * (boot/resume), OSPMs shouldn't enable the event handling, only
	 * the EC transactions are allowed to be performed.
	 */
	if (!test_bit(EC_FLAGS_QUERY_ENABLED, &ec->flags))
		return false;
	/*
	 * However, disabling the event handling is experimental for late
	 * stage (suspend), and is controlled by the boot parameter of
	 * "ec_freeze_events":
	 * 1. true:  The EC event handling is disabled before entering
	 *           the noirq stage.
	 * 2. false: The EC event handling is automatically disabled as
	 *           soon as the EC driver is stopped.
	 */
	if (ec_freeze_events)
		return acpi_ec_started(ec);
	else
		return test_bit(EC_FLAGS_STARTED, &ec->flags);
}