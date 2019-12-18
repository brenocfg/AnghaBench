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
struct acpi_nfit_system_address {int /*<<< orphan*/  range_guid; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int NFIT_UUID_MAX ; 
 scalar_t__ guid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_nfit_uuid (int) ; 

int nfit_spa_type(struct acpi_nfit_system_address *spa)
{
	int i;

	for (i = 0; i < NFIT_UUID_MAX; i++)
		if (guid_equal(to_nfit_uuid(i), (guid_t *)&spa->range_guid))
			return i;
	return -1;
}