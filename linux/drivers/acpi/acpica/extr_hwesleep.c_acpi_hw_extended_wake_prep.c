#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  sleep_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_STATE_S0 ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ACPI_X_SLEEP_ENABLE ; 
 int ACPI_X_SLEEP_TYPE_MASK ; 
 int ACPI_X_SLEEP_TYPE_POSITION ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__ acpi_gbl_FADT ; 
 int acpi_gbl_sleep_type_a ; 
 int /*<<< orphan*/  acpi_gbl_sleep_type_b ; 
 int /*<<< orphan*/  acpi_get_sleep_type_data (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_extended_wake_prep ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_hw_extended_wake_prep(u8 sleep_state)
{
	acpi_status status;
	u8 sleep_type_value;

	ACPI_FUNCTION_TRACE(hw_extended_wake_prep);

	status = acpi_get_sleep_type_data(ACPI_STATE_S0,
					  &acpi_gbl_sleep_type_a,
					  &acpi_gbl_sleep_type_b);
	if (ACPI_SUCCESS(status)) {
		sleep_type_value =
		    ((acpi_gbl_sleep_type_a << ACPI_X_SLEEP_TYPE_POSITION) &
		     ACPI_X_SLEEP_TYPE_MASK);

		(void)acpi_write((u64)(sleep_type_value | ACPI_X_SLEEP_ENABLE),
				 &acpi_gbl_FADT.sleep_control);
	}

	return_ACPI_STATUS(AE_OK);
}