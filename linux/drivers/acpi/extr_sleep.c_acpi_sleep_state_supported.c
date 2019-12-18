#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_5__ {scalar_t__ address; } ;
struct TYPE_4__ {scalar_t__ address; } ;
struct TYPE_6__ {TYPE_2__ sleep_status; TYPE_1__ sleep_control; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 TYPE_3__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_gbl_reduced_hardware ; 
 int /*<<< orphan*/  acpi_get_sleep_type_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool acpi_sleep_state_supported(u8 sleep_state)
{
	acpi_status status;
	u8 type_a, type_b;

	status = acpi_get_sleep_type_data(sleep_state, &type_a, &type_b);
	return ACPI_SUCCESS(status) && (!acpi_gbl_reduced_hardware
		|| (acpi_gbl_FADT.sleep_control.address
			&& acpi_gbl_FADT.sleep_status.address));
}