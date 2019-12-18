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
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ guid_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * prp_guids ; 

__attribute__((used)) static bool acpi_is_property_guid(const guid_t *guid)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(prp_guids); i++) {
		if (guid_equal(guid, &prp_guids[i]))
			return true;
	}

	return false;
}