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
struct acpi_ec {int reference_count; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_FLAGS_GPE_HANDLER_INSTALLED ; 
 int /*<<< orphan*/  acpi_ec_enable_gpe (struct acpi_ec*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_ec_submit_request(struct acpi_ec *ec)
{
	ec->reference_count++;
	if (test_bit(EC_FLAGS_GPE_HANDLER_INSTALLED, &ec->flags) &&
	    ec->reference_count == 1)
		acpi_ec_enable_gpe(ec, true);
}